#pragma once
#include <stdio.h>

#include "vector.h"

struct Matrix4x4 {
  float data[16];

  float& operator[](int x);
};

void printMatrix4x4(Matrix4x4* matrix);

Matrix4x4* inverseMatrix4x4(Matrix4x4* matrix);
Matrix4x4* multiplyMatrix4x4(Matrix4x4* a, Matrix4x4* b);

Matrix4x4* createIdentityMatrix4x4();
Matrix4x4* createTranslateMatrix4x4(Vector3 position);

Matrix4x4* createLookAtMatrix4x4(Vector3 position, Vector3 target, Vector3 up);