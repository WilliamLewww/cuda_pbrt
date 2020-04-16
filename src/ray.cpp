#include "ray.h"

Ray::Ray(Vector4 origin, Vector4 direction, float tMax, float time) {
  this->origin = origin;
  this->direction = direction;
  this->tMax = tMax;
  this->time = time;
}

Ray::~Ray() {

}

Vector4 Ray::operator()(float t) {
  return origin + (direction * t);
}

Vector4 offsetRayOrigin(Vector4 position, Vector4 positionError, Vector4 normal, Vector4 direction) {
  float normalError = dot(normal.getAbsolute(), positionError);

  Vector4 offset = normal * normalError;
  if (dot(direction, normal) < 0) {
    offset = -offset;
  }

  Vector4 positionOffset = position + offset;

  for (int x = 0; x < 3; x++) {
    if (offset[x] > 0) {
      positionOffset[x] = ErrorFloat::getNextFloatUp(positionOffset[x]);
    }
    else {
      if (offset[x] < 0) {
        positionOffset[x] = ErrorFloat::getNextFloatDown(positionOffset[x]);
      }
    }
  }

  return positionOffset;
}