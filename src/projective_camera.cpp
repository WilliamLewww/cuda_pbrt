#include "projective_camera.h"

ProjectiveCamera::ProjectiveCamera(TransformationMatrix* cameraToWorld, TransformationMatrix* cameraToScreen, Bounds3 screenWindow, float shutterOpen, float shutterClose, float lensRadius, float focalDistance) : Camera(cameraToWorld, shutterOpen, shutterClose) {
  this->cameraToScreen = cameraToScreen;

  this->lensRadius = lensRadius;
  this->focalDistance = focalDistance;

  Matrix4x4* first = createScaleMatrix4x4(Vector4(1920, 1080, 1, 1));
  Matrix4x4* second = createScaleMatrix4x4(Vector4(1 / (screenWindow[1][0] - screenWindow[0][0]), 1 / (screenWindow[0][1] - screenWindow[1][1]), 1, 1));
  Matrix4x4* third = createTranslateMatrix4x4(Vector4(-screenWindow[0][0], -screenWindow[1][1], 0, 1));

  screenToRaster = new TransformationMatrix(multiplyMatrix4x4(first, multiplyMatrix4x4(second, third)));
  rasterToScreen = new TransformationMatrix(screenToRaster->getInverseMatrix());
  rasterToCamera = new TransformationMatrix(multiplyMatrix4x4(cameraToScreen->getInverseMatrix(), rasterToScreen->getMatrix()));
}