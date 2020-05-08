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
protected:
  TransformationMatrix* cameraToWorld;
  float shutterOpen;
  float shutterClose;
public:
  Camera(TransformationMatrix* cameraToWorld, float shutterOpen, float shutterClose);
  ~Camera();

  void setTransformationMatrix(TransformationMatrix* cameraToWorld);
  
  virtual float generateRay(CameraSample sample, Ray* ray);
  float generateRayDifferential(CameraSample sample, RayDifferential* rayDifferential);
};