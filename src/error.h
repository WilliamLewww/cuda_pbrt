#pragma once
#include <limits>

class ErrorFloat {
public:
  float value;
  float error;

  static float machineEpsilon;
  static float gamma(int n);

  ErrorFloat();
  ErrorFloat(float value, float error = 0.0);
  ErrorFloat& operator=(ErrorFloat errorFloat);

  ErrorFloat operator*(ErrorFloat b);
  ErrorFloat operator/(ErrorFloat b);
  ErrorFloat operator+(ErrorFloat b);
  ErrorFloat operator-(ErrorFloat b);

  explicit operator float() { return value; }
  explicit operator double() { return value; }
};