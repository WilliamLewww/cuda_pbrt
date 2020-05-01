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
}