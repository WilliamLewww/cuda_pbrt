#include "camera_factory.h"

Camera* CameraGenerator::create() {
  return new Camera(nullptr, 0.0, 0.0);
}

Camera* OrthographicCameraGenerator::create() {
  return new OrthographicCamera(nullptr, Bounds3(), 0.0, 0.0, 0.0, 0.0);
}

std::map<std::string, CameraGenerator*> CameraFactory::stringCameraGeneratorMap = {
  {"OrthographicCamera", new OrthographicCameraGenerator()}
};

Camera* CameraFactory::generateCameraFromString(std::string word) {
  return stringCameraGeneratorMap[word]->create();
}