#pragma once
#include <limits>
#include <algorithm>

#include "vector.h"
#include "ray.h"

class Bounds3 {
private:
  Vector3 pointMin;
  Vector3 pointMax;
public:
  Bounds3();
  Bounds3(Vector3 point);
  Bounds3(Vector3 a, Vector3 b);

  Vector3& operator[](int index);
  Vector3 getCorner(int corner);

  Bounds3 getUnion(Vector3 b);

  bool checkRayIntersection(Ray* ray, float* firstHit, float* secondHit);
};