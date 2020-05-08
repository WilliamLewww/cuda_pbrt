#include "camera_factory.h"

Camera* CameraGenerator::create() {
  return new Camera(nullptr, 0.0, 0.0);
}

Camera* ProjectiveCameraGenerator::create() {
  return new ProjectiveCamera(nullptr, 0.0, 0.0);
}

std::map<std::string, CameraGenerator*> CameraFactory::stringCameraGeneratorMap = {
  {"ProjectiveCamera", new ProjectiveCameraGenerator()}
};

Camera* CameraFactory::generateCameraFromString(std::string word) {
  return stringCameraGeneratorMap[word]->create();
}