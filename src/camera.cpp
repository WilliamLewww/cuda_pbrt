#include "camera.h"

Ray* Camera::generateRay(CameraSample sample) {}

Camera::Camera(TransformationMatrix* cameraToWorld) {
  this->cameraToWorld = cameraToWorld;
}

Camera::~Camera() {

}

void Camera::setTransformationMatrix(TransformationMatrix* cameraToWorld) {
  this->cameraToWorld = cameraToWorld;
}