#include "error.h"

float ErrorFloat::machineEpsilon = std::numeric_limits<float>::epsilon() * 0.5;

float ErrorFloat::gamma(int n) {
  return (n * machineEpsilon) / (1 - n * machineEpsilon);
}

ErrorFloat::ErrorFloat() {
  value = 0.0;
  error = 0.0;
}

ErrorFloat::ErrorFloat(float value, float error) {
  this->value = value;
  this->error = error;
}

ErrorFloat& ErrorFloat::operator=(ErrorFloat errorFloat) {
  this->value = errorFloat.value;
  this->error = errorFloat.error;
}

ErrorFloat ErrorFloat::operator*(ErrorFloat b) {
  ErrorFloat errorFloat;
  errorFloat.value = value * b.value;

  return errorFloat;
}

ErrorFloat ErrorFloat::operator/(ErrorFloat b) {
  ErrorFloat errorFloat;
  errorFloat.value = value / b.value;

  return errorFloat;
}

ErrorFloat ErrorFloat::operator+(ErrorFloat b) {
  ErrorFloat errorFloat;
  errorFloat.value = value + b.value;

  return errorFloat;
}

ErrorFloat ErrorFloat::operator-(ErrorFloat b) {
  ErrorFloat errorFloat;
  errorFloat.value = value - b.value;

  return errorFloat;
}