#pragma once
#include <limits>

#include "vector.h"

class Ray {
private:
  Vector3 origin;
  Vector3 direction;

  mutable float tMax;
  float time;
public:
  Ray(Vector3 origin, Vector3 direction, float tMax, float time);
  ~Ray();

  Vector3 operator()(float t);
};