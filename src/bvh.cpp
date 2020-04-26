#include "bvh.h"

BVH::BVH(std::vector<Primitive*> primitiveList, int maxPrimitivesInNode, SplitMethod splitMethod) {
  this->primitiveList = primitiveList;
  this->maxPrimitivesInNode = maxPrimitivesInNode;
  this->splitMethod = splitMethod;

  if (primitiveList.size() == 0) {
    return;
  }
}