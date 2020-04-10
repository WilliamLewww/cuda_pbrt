#pragma once
#include <limits>

#include "vector.h"

class Bounds3 {
private:
  Vector3 pointMin;
  Vector3 pointMax;
public:
  Bounds3();
  Bounds3(Vector3 point);
  Bounds3(Vector3 a, Vector3 b);
};