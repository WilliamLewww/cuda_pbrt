#pragma once
#include <limits>

#include "vector.h"
#include "error.h"

class Ray {  
public:
  Vector4 origin;
  Vector4 direction;

  mutable float tMax;
  float time;

  Ray();
  Ray(Vector4 origin, Vector4 direction, float tMax = std::numeric_limits<float>::max(), float time = 0.0f);
  ~Ray();

  Vector4 operator()(float t);
};

class RayDifferential : public Ray {
public:
  bool hasDifferentials;
  Vector4 rxOrigin;
  Vector4 ryOrigin;
  Vector4 rxDirection;
  Vector4 ryDirection;

  RayDifferential();
  RayDifferential(Ray ray);
  RayDifferential(Vector4 origin, Vector4 direction, float tMax = std::numeric_limits<float>::max(), float time = 0.0f);

  void scaleDifferentials(float s);
};

Vector4 offsetRayOrigin(Vector4 position, Vector4 positionError, Vector4 normal, Vector4 direction);