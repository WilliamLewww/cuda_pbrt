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

BVH::BVH(std::vector<Primitive*> primitiveList, int maxPrimitivesInNode, SplitMethod splitMethod) {
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
  BVHBuildNode* root;

  if (splitMethod == SplitMethod::HLBVH) {

  }
  else {
    root = recursiveBuild(area, primitiveInformationList, 0, primitiveList.size(), &totalNodes, orderedPrimitiveList);
  }

  primitiveList.swap(orderedPrimitiveList);
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
  }

  return node;
}