#pragma once
#include <math.h>

class Vector2 {
private:
  float x, y;
public:
  Vector2();
  Vector2(float x, float y);

  float& operator[](int index);
};

class Vector4 {
private:
  float x, y, z, w;
public:
  Vector4();
  Vector4(float x, float y, float z, float w);
  Vector4& operator=(Vector4 b);

  float getLengthSquared();
  float getLength();

  Vector4 getAbsolute();
  
  float& operator[](int index);
  Vector4 operator*(float value);
  Vector4 operator*=(float value);
  Vector4 operator/(float value);
  Vector4 operator+(Vector4 b);
  Vector4 operator+=(Vector4 b);
  Vector4 operator-();
  Vector4 operator-(Vector4 b);
  bool operator!=(Vector4 b);
};

Vector4 normalize(Vector4 a);
Vector4 cross(Vector4 a, Vector4 b);
float dot(Vector4 a, Vector4 b);