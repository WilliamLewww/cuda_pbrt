#pragma once
#include "projective_camera.h"

class OrthographicCamera : public ProjectiveCamera {
private:
  Vector4 dxCamera;
  Vector4 dyCamera;
public:
  OrthographicCamera(TransformationMatrix* cameraToWorld, Bounds3 screenWindow, float shutterOpen, float shutterClose, float lensRadius, float focalDistance);
};