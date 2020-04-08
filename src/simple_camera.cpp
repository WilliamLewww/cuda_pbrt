#include "simple_camera.h"

SimpleCamera::SimpleCamera(TransformationMatrix* cameraToWorld) : Camera(cameraToWorld) {
  nearPlaneZ = 1.0;
  farPlaneZ = 10.0;
}

SimpleCamera::~SimpleCamera() {

}

Ray* SimpleCamera::generateRay(CameraSample sample) {
  Vector3 origin(sample.filmPosition[0], sample.filmPosition[1], 0);
  Vector3 direction(sample.lensPosition[0] - sample.filmPosition[0], sample.lensPosition[1] - sample.filmPosition[1], nearPlaneZ);

  Ray* ray = new Ray((*cameraToWorld)(origin), (*cameraToWorld)(direction));
  return ray;
}