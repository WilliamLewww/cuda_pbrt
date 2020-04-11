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