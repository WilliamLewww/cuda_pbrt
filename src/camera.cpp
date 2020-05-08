#include "camera.h"

float Camera::generateRay(CameraSample sample, Ray* ray) {}

Camera::Camera(TransformationMatrix* cameraToWorld, float shutterOpen, float shutterClose) {
  this->cameraToWorld = cameraToWorld;
  this->shutterOpen = shutterOpen;
  this->shutterClose = shutterClose;
}

Camera::~Camera() {

}

void Camera::setTransformationMatrix(TransformationMatrix* cameraToWorld) {
  this->cameraToWorld = cameraToWorld;
}

float Camera::generateRayDifferential(CameraSample sample, RayDifferential* rayDifferential) {
  float wt = generateRay(sample, rayDifferential);

  CameraSample sshift = sample;
  sshift.filmPosition[0] += 1;
  Ray rx;
  float wtx = generateRay(sshift, &rx);
  if (wtx == 0) {
    return 0;
  }
  rayDifferential->rxOrigin = rx.origin;
  rayDifferential->rxDirection = rx.direction;

  sshift.filmPosition[0] -= 1;
  sshift.filmPosition[1] += 1;
  Ray ry;
  float wty = generateRay(sshift, &ry);
  if (wty == 0.f) {
    return 0;
  }

  rayDifferential->ryOrigin = ry.origin;
  rayDifferential->ryDirection = ry.direction;

  rayDifferential->hasDifferentials = true;
  return wt;
}