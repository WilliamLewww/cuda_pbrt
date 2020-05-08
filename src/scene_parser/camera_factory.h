#pragma once
#include <map>
#include <string>

#include "../camera.h"
#include "../projective_camera.h"
#include "../transformation_matrix.h"

class CameraGenerator {
public:
  virtual Camera* create();
};

class ProjectiveCameraGenerator : public CameraGenerator {
public:
  virtual Camera* create();
};

class CameraFactory {
private:
  static std::map<std::string, CameraGenerator*> stringCameraGeneratorMap;
public:
  static Camera* generateCameraFromString(std::string word);
};