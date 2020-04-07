#pragma once
#include "camera.h"

class SimpleCamera : public Camera {
private:
public:
  SimpleCamera();
  ~SimpleCamera();
  
  Ray* generateRay(CameraSample sample) override;
};