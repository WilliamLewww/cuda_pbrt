#include "camera_factory.h"

Camera* CameraGenerator::create() {
  return new Camera();
}

Camera* SimpleCameraGenerator::create() {
  return new SimpleCamera();
}

std::map<std::string, CameraGenerator*> CameraFactory::stringCameraGeneratorMap = {
  {"SimpleCamera", new SimpleCameraGenerator()}
};

Camera* CameraFactory::generateCameraFromString(std::string word) {
  return stringCameraGeneratorMap[word]->create();
}