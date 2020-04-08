#pragma once
#include "camera.h"

class SimpleCamera : public Camera {
private:
  float nearPlaneZ;
  float farPlaneZ;
public:
  SimpleCamera(TransformationMatrix* cameraToWorld);
  ~SimpleCamera();
  
  Ray* generateRay(CameraSample sample) override;
};