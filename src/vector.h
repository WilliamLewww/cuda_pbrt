#pragma once

class Vector3 {
private:
  float x, y, z;
public:
  Vector3();
  Vector3(float x, float y, float z);
  
  float& operator[](int index);
};