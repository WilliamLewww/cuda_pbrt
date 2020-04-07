#pragma once
#include "camera.h"

class SimpleCamera : public Camera {
private:
public:
  SimpleCamera(TransformationMatrix* cameraToWorld);
  ~SimpleCamera();
  
  Ray* generateRay(CameraSample sample) override;
};