#pragma once
#include "vector.h"

struct Matrix4x4 {
  float data[16];

  float& operator[](int x);
};

Matrix4x4* inverseMatrix4x4(Matrix4x4* matrix);
Matrix4x4* multiplyMatrix4x4(Matrix4x4* a, Matrix4x4* b);

Matrix4x4* createIdentityMatrix4x4();
Matrix4x4* createTranslateMatrix4x4();