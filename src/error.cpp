#include "error.h"

float ErrorFloat::machineEpsilon = std::numeric_limits<float>::epsilon() * 0.5;
float ErrorFloat::shadownEpsilon = 0.0001;

float ErrorFloat::gamma(int n) {
  return (n * machineEpsilon) / (1 - n * machineEpsilon);
}

float ErrorFloat::getBitsToFloat(uint32_t value) {
  float f;
  memcpy(&f, &value, sizeof(uint32_t));
  return f;
}

float ErrorFloat::getFloatToBits(uint32_t value) {
  uint32_t ui;
  memcpy(&ui, &value, sizeof(float));
  return ui;
}

float ErrorFloat::getNextFloatUp(float value) {
  if (isinf(value) && value > 0.0) {
    return value;
  }

  if (value == -0.0f) {
    value = 0.0f;
  }

  uint32_t ui = getFloatToBits(value);
  if (value >= 0) {
    ui += 1;
  }
  else {
    ui -= 1;
  }

  return getBitsToFloat(ui);
}

float ErrorFloat::getNextFloatDown(float value) {
  if (isinf(value) && value > 0.0) {
    return value;
  }

  if (value == 0.0f) {
    value = -0.0f;
  }

  uint32_t ui = getFloatToBits(value);
  if (value > 0) {
    ui -= 1;
  }
  else {
    ui += 1;
  }

  return getBitsToFloat(ui);
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

bool ErrorFloat::operator==(ErrorFloat b) {
  return (this->value == b.value && this->error == b.error);
}

ErrorFloat ErrorFloat::operator*(ErrorFloat b) {
  ErrorFloat errorFloat;
  errorFloat.value = value * b.value;

  errorFloat.error = fabs(b.value * error) + fabs(value * b.error) + error * b.error + machineEpsilon * fabs(value * b.value);

  return errorFloat;
}

ErrorFloat ErrorFloat::operator/(ErrorFloat b) {
  ErrorFloat errorFloat;
  errorFloat.value = value / b.value;

  errorFloat.error = (fabs(value) + error) / (fabs(b.value) - b.error) - fabs(value / b.value) + machineEpsilon * (fabs(value) + error) / (fabs(b.value) - error);

  return errorFloat;
}

ErrorFloat ErrorFloat::operator+(ErrorFloat b) {
  ErrorFloat errorFloat;
  errorFloat.value = value + b.value;

  errorFloat.error = error + b.error + machineEpsilon * (fabs(value + b.value) + error + b.error);

  return errorFloat;
}

ErrorFloat ErrorFloat::operator-(ErrorFloat b) {
  ErrorFloat errorFloat;
  errorFloat.value = value - b.value;

  errorFloat.error = error + b.error + machineEpsilon * (fabs(value - b.value) + error + b.error);

  return errorFloat;
}

float ErrorFloat::getLowerBound() {
  return getNextFloatUp(value + error);
}

float ErrorFloat::getUpperBound() {
  return getNextFloatDown(value + error);
}