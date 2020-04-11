#pragma once
#include <limits>

#include "vector.h"

class Ray {  
public:
  Vector3 origin;
  Vector3 direction;

  mutable float tMax;
  float time;

  Ray(Vector3 origin, Vector3 direction, float tMax = std::numeric_limits<float>::max(), float time = 0.0f);
  ~Ray();

  Vector3 operator()(float t);
};