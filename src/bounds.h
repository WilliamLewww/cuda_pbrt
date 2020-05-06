#pragma once
#include <limits>

#include "vector.h"
#include "ray.h"
#include "error.h"

class Bounds3 {
private:
  Vector4 pointMin;
  Vector4 pointMax;
public:  
  Bounds3();
  Bounds3(Vector4 point);
  Bounds3(Vector4 a, Vector4 b);

  Vector4& operator[](int index);
  Vector4 getCorner(int corner);

  Bounds3 getUnion(Vector4 b);
  Bounds3 getUnion(Bounds3 b);

  Vector4 getDiagonal();
  int getMaximumExtent();

  bool checkRayIntersectionPredicate(Ray* ray, float* firstHit, float* secondHit);
  bool checkRayIntersectionPredicate(Ray* ray, Vector4 inverseDirection, bool directionIsNegative[3]);
};