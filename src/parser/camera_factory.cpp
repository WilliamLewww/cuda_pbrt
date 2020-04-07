#include "camera_factory.h"

Camera* CameraGenerator::create() {
  return new Camera(nullptr);
}

Camera* SimpleCameraGenerator::create() {
  return new SimpleCamera(nullptr);
}

std::map<std::string, CameraGenerator*> CameraFactory::stringCameraGeneratorMap = {
  {"SimpleCamera", new SimpleCameraGenerator()}
};

Camera* CameraFactory::generateCameraFromString(std::string word) {
  return stringCameraGeneratorMap[word]->create();
}