#pragma once
#include "camera.h"

class ProjectiveCamera : public Camera {
protected:
  TransformationMatrix* cameraToScreen;
  TransformationMatrix* rasterToCamera;
  TransformationMatrix* screenToRaster;
  TransformationMatrix* rasterToScreen;

  float lensRadius;
  float focalDistance;
public:
  ProjectiveCamera(TransformationMatrix* cameraToWorld, TransformationMatrix* cameraToScreen, Bounds3 screenWindow, float shutterOpen, float shutterClose, float lensRadius, float focalDistance);
};