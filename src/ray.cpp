#include "ray.h"

Ray::Ray(Vector3 origin, Vector3 direction, float tMax, float time) {
  this->origin = origin;
  this->direction = direction;
  this->tMax = tMax;
  this->time = time;
}

Ray::~Ray() {

}

Vector3 Ray::operator()(float t) {
  return origin + (direction * t);
}