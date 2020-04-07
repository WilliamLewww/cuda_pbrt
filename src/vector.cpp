#include "vector.h"

Vector2::Vector2() {
  x = 0.0;
  y = 0.0;
}

Vector2::Vector2(float x, float y) {
  this->x = x;
  this->y = y;
}

float& Vector2::operator[](int index) {
  if (index == 0) { return x; }
  if (index == 1) { return y; }
}

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

float Vector3::getLength() {
  return sqrt(x * x + y * y + z * z);
}

float& Vector3::operator[](int index) {
  if (index == 0) { return x; }
  if (index == 1) { return y; }
  if (index == 2) { return z; }
}

Vector3 Vector3::operator*(float value) {
  return Vector3(x * value, y * value, z * value);
}

Vector3 Vector3::operator/(float value) {
  return Vector3(x / value, y / value, z / value);
}

Vector3 Vector3::operator+(Vector3 b) {
  return Vector3(x + b[0], y + b[1], z + b[2]);
}

Vector3 Vector3::operator-(Vector3 b) {
  return Vector3(x - b[0], y - b[1], z - b[2]);
}

Vector3 normalize(Vector3 a) {
  return a / a.getLength();
}

Vector3 cross(Vector3 a, Vector3 b) {
  return Vector3(
    (a[1] * b[2]) - (a[2] * b[1]),
    (a[2] * b[0]) - (a[0] * b[2]),
    (a[0] * b[1]) - (a[1] * b[0])
  );
}