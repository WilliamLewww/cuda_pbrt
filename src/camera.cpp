#include "camera.h"

Camera::Camera(TransformationMatrix* cameraToWorld) {
  this->cameraToWorld = cameraToWorld;
}

Camera::~Camera() {

}

void Camera::setTransformationMatrix(TransformationMatrix* cameraToWorld) {
  this->cameraToWorld = cameraToWorld;
}

Ray* Camera::generateRay(CameraSample sample) {
  return nullptr;
}