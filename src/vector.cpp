#include "vector.h"

Vector3::Vector3() {
  x = 0.0;
  y = 0.0;
  z = 0.0;
}

Vector3::Vector3(float x, float y, float z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

float& Vector3::operator[](int index) {
  if (index == 0) { return x; }
  if (index == 1) { return y; }
  if (index == 2) { return z; }
}