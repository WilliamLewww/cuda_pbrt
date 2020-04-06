#pragma once
#include "vector.h"
#include "ray.h"

struct CameraSample {
  Vector2 filmPosition;
  Vector2 lensPosition;
  float time;
};

class Camera {
private:
public:
  virtual Ray* generateRay(CameraSample sample);
};