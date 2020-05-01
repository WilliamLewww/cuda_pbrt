#pragma once
#include <vector>

#include "primitive.h"
#include "memory_area.h"

enum class SplitMethod {
  SAH, HLBVH, Middle, EqualCounts
};

struct BVHPrimitiveInformation {
  BVHPrimitiveInformation(uint64_t primitiveNumber, Bounds3 bounds);

  uint64_t primitiveNumber;
  Bounds3 bounds;
  Vector4 centroid;
};

struct BVHBuildNode {
  void initializeLeaf(int firstPrimitiveOffset, int primitiveCount, Bounds3 bounds);
  void initializeInterior(int splitAxis, BVHBuildNode* firstChild, BVHBuildNode* secondChild);
  
  Bounds3 bounds;
  BVHBuildNode* children[2];

  int splitAxis;
  int firstPrimitiveOffset;
  int primitiveCount;
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