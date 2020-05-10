#pragma once
#include "camera.h"

class ProjectiveCamera : public Camera {
protected:
  TransformationMatrix* cameraToScreen;
  TransformationMatrix* rasterToCamera;
  TransformationMatrix* screenToRaster;
  TransformationMatrix* rasterToScreen;
public:
};