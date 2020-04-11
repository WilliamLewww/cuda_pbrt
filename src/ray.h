#pragma once
#include <limits>

#include "vector.h"

class Ray {  
public:
  Vector4 origin;
  Vector4 direction;

  mutable float tMax;
  float time;

  Ray(Vector4 origin, Vector4 direction, float tMax = std::numeric_limits<float>::max(), float time = 0.0f);
  ~Ray();

  Vector4 operator()(float t);
};