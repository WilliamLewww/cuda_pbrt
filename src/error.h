#pragma once
#include <limits>

class ErrorFloat {
private:
  float value;
  float error;
public:
  static float gamma(int n);

  ErrorFloat();
  ErrorFloat(float value, float error = 0.0);
  ErrorFloat& operator=(ErrorFloat errorFloat);
};