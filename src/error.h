#pragma once
#include <limits>
#include <cstdint>
#include <cstring>
#include <math.h>

class ErrorFloat {
public:
  float value;
  float error;

  static float machineEpsilon;
  static float gamma(int n);

  static float getBitsToFloat(uint32_t value);
  static float getFloatToBits(uint32_t value);

  static float getNextFloatUp(float value);
  static float getNextFloatDown(float value);

  ErrorFloat();
  ErrorFloat(float value, float error = 0.0);
  ErrorFloat& operator=(ErrorFloat errorFloat);

  bool operator==(ErrorFloat b);

  ErrorFloat operator*(ErrorFloat b);
  ErrorFloat operator/(ErrorFloat b);
  ErrorFloat operator+(ErrorFloat b);
  ErrorFloat operator-(ErrorFloat b);

  float getLowerBound();
  float getUpperBound();

  explicit operator float() { return value; }
  explicit operator double() { return value; }
};