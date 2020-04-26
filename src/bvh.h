#pragma once
#include <vector>

#include "primitive.h"

enum class SplitMethod {
  SAH, HLBVH, Middle, EqualCounts
};

class BVH : public Aggregate {
private:
  int maxPrimitivesInNode;
  SplitMethod splitMethod;
  std::vector<Primitive*> primitiveList;
public:
  BVH(std::vector<Primitive*> primitiveList, int maxPrimitivesInNode, SplitMethod splitMethod);
  ~BVH();
};