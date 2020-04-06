#pragma once

class Vector2 {
private:
  float x, y;
public:
  Vector2();
  Vector2(float x, float y);

  float& operator[](int index);
};

class Vector3 {
private:
  float x, y, z;
public:
  Vector3();
  Vector3(float x, float y, float z);
  
  float& operator[](int index);
  Vector3 operator*(float value);
  Vector3 operator+(Vector3 b);
};