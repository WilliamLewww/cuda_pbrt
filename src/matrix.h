#pragma once

struct Matrix4x4 {
  float data[16];

  float& operator[](int x);
};

Matrix4x4* createIdentityMatrix4x4();
Matrix4x4* inverseMatrix4x4(Matrix4x4* matrix);