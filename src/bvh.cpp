#include "bvh.h"

BVHPrimitiveInformation::BVHPrimitiveInformation(uint64_t primitiveNumber, Bounds3 bounds) {
  this->primitiveNumber = primitiveNumber;
  this->bounds = bounds;
  this->centroid = bounds[0] * 0.5f + bounds[1] * 0.5f;
}

void BVHBuildNode::initializeLeaf(int firstPrimitiveOffset, int primitiveCount, Bounds3 bounds) {
  this->firstPrimitiveOffset = firstPrimitiveOffset;
  this->primitiveCount = primitiveCount;
  this->bounds = bounds;

  children[0] = nullptr;
  children[1] = nullptr;
}

void BVHBuildNode::initializeInterior(int splitAxis, BVHBuildNode* firstChild, BVHBuildNode* secondChild) {
  children[0] = firstChild;
  children[1] = secondChild;

  this->bounds = firstChild->bounds.getUnion(secondChild->bounds);
  this->splitAxis = splitAxis;
  this->primitiveCount = 0;
}

std::string BVHBuildNode::toString() {
  std::string printString = "";

  if (children[0] == nullptr && children[1] == nullptr) {
    printString += "Leaf: ";
  }
  else {
    printString += std::string("Interior: ");
  }
  printString += std::string("(") + std::to_string((int)bounds[0][0]) + std::string(", ") + std::to_string((int)bounds[0][1]) + std::string(", ") + std::to_string((int)bounds[0][2]) + std::string(") ");
  printString += std::string("(") + std::to_string((int)bounds[1][0]) + std::string(", ") + std::to_string((int)bounds[1][1]) + std::string(", ") + std::to_string((int)bounds[1][2]) + std::string(")");
  
  return printString;
}

int BVH::flattenBuildTree(BVHBuildNode* buildNode, int* offset) {
  BVHLinearNode* linearNode = &linearNodes[*offset];
  linearNode->bounds = buildNode->bounds;
  int tempOffset = *offset;
  *offset += 1;
  if (buildNode->primitiveCount > 0) {
    linearNode->primitivesOffset = buildNode->firstPrimitiveOffset;
    linearNode->primitiveCount = buildNode->primitiveCount;
  }
  else {
    linearNode->axis = buildNode->splitAxis;
    linearNode->primitiveCount = 0;
    flattenBuildTree(buildNode->children[0], offset);
    linearNode->secondChildOffset = flattenBuildTree(buildNode->children[1], offset);
  }

  return tempOffset;
}

BVH::BVH(std::vector<Primitive*> primitiveList, int maxPrimitivesInNode, SplitMethod splitMethod) {
  this->buildRoot = nullptr;
  this->linearNodes = nullptr;

  this->primitiveList = primitiveList;
  this->maxPrimitivesInNode = maxPrimitivesInNode;
  this->splitMethod = splitMethod;

  if (primitiveList.size() == 0) {
    return;
  }

  std::vector<BVHPrimitiveInformation> primitiveInformationList;
  for (int x = 0; x < primitiveList.size(); x++) {
    primitiveInformationList.emplace_back(x, primitiveList[x]->worldBounds());
  }

  MemoryArea area(1024 * 1024);
  int totalNodes = 0;
  std::vector<Primitive*> orderedPrimitiveList;

  if (splitMethod == SplitMethod::HLBVH) {

  }
  else {
    buildRoot = recursiveBuild(area, primitiveInformationList, 0, primitiveList.size(), &totalNodes, orderedPrimitiveList);
  }

  primitiveList.swap(orderedPrimitiveList);

  linearNodes = allocateAligned<BVHLinearNode>(totalNodes);
  int offset = 0;
  flattenBuildTree(buildRoot, &offset);
}

BVHBuildNode* BVH::recursiveBuild(MemoryArea& area, std::vector<BVHPrimitiveInformation>& primitiveInformationList, int start, int end, int* totalNodes, std::vector<Primitive*>& orderedPrimitiveList) {
  BVHBuildNode* node = area.allocate<BVHBuildNode>();
  *totalNodes += 1;

  Bounds3 bounds = primitiveInformationList[start].bounds;
  for (int x = start + 1; x < end; x++) {
    bounds = bounds.getUnion(primitiveInformationList[x].bounds);
  }

  int primitiveCount = end - start;
  if (primitiveCount == 1) {
    int firstPrimitiveOffset = orderedPrimitiveList.size();
    for (int x = start; x < end; x++) {
      int primitiveNumber = primitiveInformationList[x].primitiveNumber;
      orderedPrimitiveList.push_back(primitiveList[primitiveNumber]);
    }
    node->initializeLeaf(firstPrimitiveOffset, primitiveCount, bounds);
    return node;
  }
  else {
    Bounds3 centroidBounds = Bounds3(primitiveInformationList[start].centroid);
    for (int x = start + 1; x < end; x++) {
      centroidBounds = centroidBounds.getUnion(primitiveInformationList[x].centroid);
    }
    int dimension = centroidBounds.getMaximumExtent();

    int mid = (start + end) / 2;
    if (centroidBounds[1][dimension] == centroidBounds[0][dimension]) {
      int firstPrimitiveOffset = orderedPrimitiveList.size();
      for (int x = start; x < end; x++) {
        int primitiveNumber = primitiveInformationList[x].primitiveNumber;
        orderedPrimitiveList.push_back(primitiveList[primitiveNumber]);
      }
      node->initializeLeaf(firstPrimitiveOffset, primitiveCount, bounds);
      return node;
    }
    else {
      if (splitMethod == SplitMethod::Middle) {
        float splitPosition = (centroidBounds[0][dimension] + centroidBounds[1][dimension]) / 2;
        BVHPrimitiveInformation* midPointer = std::partition(&primitiveInformationList[start], &primitiveInformationList[end - 1] + 1,
          [dimension, splitPosition](BVHPrimitiveInformation primitiveInformation) {
            return primitiveInformation.centroid[dimension] < splitPosition;
          }
        );

        mid = midPointer - &primitiveInformationList[0];
      }
      if (splitMethod == SplitMethod::EqualCounts) {
        std::nth_element(&primitiveInformationList[start], &primitiveInformationList[mid], &primitiveInformationList[end - 1] + 1,
          [dimension](BVHPrimitiveInformation a, BVHPrimitiveInformation b) {
            return a.centroid[dimension] < b.centroid[dimension];
          }
        );
      }
      node->initializeInterior(
        dimension,
        recursiveBuild(area, primitiveInformationList, start, mid, totalNodes, orderedPrimitiveList),
        recursiveBuild(area, primitiveInformationList, mid, end, totalNodes, orderedPrimitiveList)
      );
    }
  }

  return node;
}

void BVH::printBuildTree(BVHBuildNode* root, int offset) {
  if (root == nullptr) {
    root = buildRoot;
  }

  std::string offsetString(offset, ' ');
  printf("%s%s\n", offsetString.c_str(), root->toString().c_str());

  if (root->children[0] != nullptr) {
    printBuildTree(root->children[0], offset + 2);
  }
  if (root->children[1] != nullptr) {
    printBuildTree(root->children[1], offset + 2);
  }
}

void BVH::printLinearTree(int nodeOffset, int offset) {
  std::string offsetString(offset, ' ');
  std::string nodeString = "";
  nodeString += std::string("(") + std::to_string((int)linearNodes[nodeOffset].bounds[0][0]) + std::string(", ") + std::to_string((int)linearNodes[nodeOffset].bounds[0][1]) + std::string(", ") + std::to_string((int)linearNodes[nodeOffset].bounds[0][2]) + std::string(") ");
  nodeString += std::string("(") + std::to_string((int)linearNodes[nodeOffset].bounds[1][0]) + std::string(", ") + std::to_string((int)linearNodes[nodeOffset].bounds[1][1]) + std::string(", ") + std::to_string((int)linearNodes[nodeOffset].bounds[1][2]) + std::string(")");

  if (linearNodes[nodeOffset].primitiveCount > 0) {
    nodeString = std::string("Leaf: ") + nodeString;
    printf("%s%s\n", offsetString.c_str(), nodeString.c_str());
  }
  else {
    nodeString = std::string("Interior: ") + nodeString;
    printf("%s%s\n", offsetString.c_str(), nodeString.c_str());

    printLinearTree(nodeOffset + 1, offset + 2);
    printLinearTree(linearNodes[nodeOffset].secondChildOffset, offset + 2);
  }
}