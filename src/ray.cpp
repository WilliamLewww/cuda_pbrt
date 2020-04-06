#include "ray.h"

Ray::Ray(Vector3 origin, Vector3 direction, float tMax = std::numeric_limits<int>::max(), float time = 0.0f) {
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