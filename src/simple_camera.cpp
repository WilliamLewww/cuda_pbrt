#include "simple_camera.h"

SimpleCamera::SimpleCamera(TransformationMatrix* cameraToWorld) : Camera(cameraToWorld) {

}

SimpleCamera::~SimpleCamera() {

}

Ray* SimpleCamera::generateRay(CameraSample sample) {
  return nullptr;
}