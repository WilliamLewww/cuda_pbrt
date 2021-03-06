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

Matrix4x4* createTranslateMatrix4x4(Vector4 position);
Matrix4x4* createScaleMatrix4x4(Vector4 size);

Matrix4x4* createLookAtMatrix4x4(Vector4 position, Vector4 target, Vector4 up);

Matrix4x4* createOrthographicMatrix4x4(float zNear, float zFar);