#include "orthographic_camera.h"

OrthographicCamera::OrthographicCamera(TransformationMatrix* cameraToWorld, Bounds3 screenWindow, float shutterOpen, float shutterClose, float lensRadius, float focalDistance) : ProjectiveCamera(cameraToWorld, new TransformationMatrix(createOrthographicMatrix4x4(0, 1)), screenWindow, shutterOpen, shutterClose, lensRadius, focalDistance) {
  dxCamera = (*rasterToCamera)(Vector4(1, 0, 0, 0));
  dyCamera = (*rasterToCamera)(Vector4(0, 1, 0, 0));
}

float OrthographicCamera::generateRay(CameraSample sample, Ray* ray) {
  Vector4 filmPosition = Vector4(sample.filmPosition[0], sample.filmPosition[1], 0, 1);
  Vector4 cameraPosition = (*rasterToCamera)(filmPosition);

  *ray = Ray(cameraPosition, Vector4(0, 0, 1, 0));

  // if (lensRadius > 0) {
  //   Vector4 lensPosition = lensRadius * concentricSampleDisk(sample.lensPosition);
  //   float ft = focalDistance / ray->d[2];
  //   Vector4 focusPosition = (*ray)(ft);

  //   ray->origin = Vector4(lensPosition[0], lensPosition[1], 0, 1);
  //   ray->direction = normalize(focusPosition - ray->origin);
  // }

  ray->time = linearInterpolate(sample.time, shutterOpen, shutterClose);
  *ray = (*cameraToWorld)(*ray);
  return 1;
}