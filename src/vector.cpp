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

Vector4::Vector4() {
  x = 0.0;
  y = 0.0;
  z = 0.0;
  w = 0.0;
}

Vector4::Vector4(float x, float y, float z, float w) {
  this->x = x;
  this->y = y;
  this->z = z;
  this->w = w;
}

Vector4& Vector4::operator=(Vector4 b) {
  this->x = b[0];
  this->y = b[1];
  this->z = b[2];
  this->w = b[3];
  
  return *this;
}

float Vector4::getLength() {
  return sqrt((x * x) + (y * y) + (z * z));
}

float& Vector4::operator[](int index) {
  if (index == 0) { return x; }
  if (index == 1) { return y; }
  if (index == 2) { return z; }
  if (index == 3) { return w; }
}

Vector4 Vector4::operator*(float value) {
  return Vector4(x * value, y * value, z * value, w * value);
}

Vector4 Vector4::operator/(float value) {
  return Vector4(x / value, y / value, z / value, w / value);
}

Vector4 Vector4::operator+(Vector4 b) {
  return Vector4(x + b[0], y + b[1], z + b[2], w + b[3]);
}

Vector4 Vector4::operator-() {
  return Vector4(-x, -y, -z, -w);
}

Vector4 Vector4::operator-(Vector4 b) {
  return Vector4(x - b[0], y - b[1], z - b[2], w - b[3]);
}

bool Vector4::operator!=(Vector4 b) {
  return (x != b[0] || y != b[1] || z != b[2] || w != b[3]);
}

Vector4 normalize(Vector4 a) {
  return a / a.getLength();
}

Vector4 cross(Vector4 a, Vector4 b) {
  return Vector4(
    (a[1] * b[2]) - (a[2] * b[1]),
    (a[2] * b[0]) - (a[0] * b[2]),
    (a[0] * b[1]) - (a[1] * b[0]),
    1.0
  );
}

float dot(Vector4 a, Vector4 b) {
  return (a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]) + (a[3] * b[3]);
}