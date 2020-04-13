#include "simple_camera.h"

SimpleCamera::SimpleCamera(TransformationMatrix* cameraToWorld) : Camera(cameraToWorld) {
  nearPlaneZ = 1.0;
  farPlaneZ = 10.0;
}

SimpleCamera::~SimpleCamera() {

}

Ray* SimpleCamera::generateRay(CameraSample sample) {
  Vector4 origin(sample.filmPosition[0], sample.filmPosition[1], 0, 1);
  Vector4 direction(0, 0, 1, 0);

  Ray* ray = new Ray((*cameraToWorld)(origin), (*cameraToWorld)(direction));
  return ray;
}