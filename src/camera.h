#pragma once
#include "transformation_matrix.h"
#include "vector.h"
#include "ray.h"

struct CameraSample {
  Vector2 filmPosition;
  Vector2 lensPosition;
  float time;
};

class Camera {
private:
  TransformationMatrix* cameraToWorld;
public:
  Camera(TransformationMatrix* cameraToWorld);
  ~Camera();

  void setTransformationMatrix(TransformationMatrix* cameraToWorld);
  
  virtual Ray* generateRay(CameraSample sample);
};