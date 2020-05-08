#include "ray.h"

Ray::Ray() {

}

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

RayDifferential::RayDifferential() : Ray() {
  hasDifferentials = false;
}

RayDifferential::RayDifferential(Ray ray) : Ray(ray) {
  hasDifferentials = false;
}

RayDifferential::RayDifferential(Vector4 origin, Vector4 direction, float tMax, float time) : Ray(origin, direction, tMax, time) {
  hasDifferentials = false;
}

void RayDifferential::scaleDifferentials(float s) {
  rxOrigin = origin + (rxOrigin - origin) * s;
  ryOrigin = origin + (ryOrigin - origin) * s;
  rxDirection = direction + (rxDirection - direction) * s;
  ryDirection = direction + (ryDirection - direction) * s;
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