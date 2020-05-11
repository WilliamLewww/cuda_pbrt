#include "orthographic_camera.h"

OrthographicCamera::OrthographicCamera(TransformationMatrix* cameraToWorld, Bounds3 screenWindow, float shutterOpen, float shutterClose, float lensRadius, float focalDistance) : ProjectiveCamera(cameraToWorld, new TransformationMatrix(createOrthographicMatrix4x4(0, 1)), screenWindow, shutterOpen, shutterClose, lensRadius, focalDistance) {
  dxCamera = (*rasterToCamera)(Vector4(1, 0, 0, 0));
  dyCamera = (*rasterToCamera)(Vector4(0, 1, 0, 0));
}