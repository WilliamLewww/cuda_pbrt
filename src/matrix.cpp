#include "matrix.h"

float& Matrix4x4::operator[](int x) {
  return this->data[x];
}

Matrix4x4* createIdentityMatrix4x4() {
  Matrix4x4* matrix = new Matrix4x4;
  (*matrix)[0] = 1.0;  (*matrix)[1] = 0.0;  (*matrix)[2] = 0.0;  (*matrix)[3] = 0.0;
  (*matrix)[4] = 0.0;  (*matrix)[5] = 1.0;  (*matrix)[6] = 0.0;  (*matrix)[7] = 0.0;
  (*matrix)[8] = 0.0;  (*matrix)[9] = 0.0;  (*matrix)[10] = 1.0; (*matrix)[11] = 0.0;
  (*matrix)[12] = 0.0; (*matrix)[13] = 0.0; (*matrix)[14] = 0.0; (*matrix)[15] = 1.0;

  return matrix;
}

Matrix4x4* inverseMatrix4x4(Matrix4x4* matrix) {
  Matrix4x4* inverseMatrix = new Matrix4x4;
  (*inverseMatrix)[0] = (*matrix)[5]  * (*matrix)[10] * (*matrix)[15] - (*matrix)[5]  * (*matrix)[11] * (*matrix)[14] - (*matrix)[9]  * (*matrix)[6]  * (*matrix)[15] + (*matrix)[9]  * (*matrix)[7]  * (*matrix)[14] +(*matrix)[13] * (*matrix)[6]  * (*matrix)[11] - (*matrix)[13] * (*matrix)[7]  * (*matrix)[10];
  (*inverseMatrix)[1] = -(*matrix)[1]  * (*matrix)[10] * (*matrix)[15] + (*matrix)[1]  * (*matrix)[11] * (*matrix)[14] + (*matrix)[9]  * (*matrix)[2] * (*matrix)[15] - (*matrix)[9]  * (*matrix)[3] * (*matrix)[14] - (*matrix)[13] * (*matrix)[2] * (*matrix)[11] + (*matrix)[13] * (*matrix)[3] * (*matrix)[10];
  (*inverseMatrix)[2] = (*matrix)[1]  * (*matrix)[6] * (*matrix)[15] - (*matrix)[1]  * (*matrix)[7] * (*matrix)[14] - (*matrix)[5]  * (*matrix)[2] * (*matrix)[15] + (*matrix)[5]  * (*matrix)[3] * (*matrix)[14] + (*matrix)[13] * (*matrix)[2] * (*matrix)[7] - (*matrix)[13] * (*matrix)[3] * (*matrix)[6];
  (*inverseMatrix)[3] = -(*matrix)[1] * (*matrix)[6] * (*matrix)[11] + (*matrix)[1] * (*matrix)[7] * (*matrix)[10] + (*matrix)[5] * (*matrix)[2] * (*matrix)[11] - (*matrix)[5] * (*matrix)[3] * (*matrix)[10] - (*matrix)[9] * (*matrix)[2] * (*matrix)[7] + (*matrix)[9] * (*matrix)[3] * (*matrix)[6];
  (*inverseMatrix)[4] = -(*matrix)[4]  * (*matrix)[10] * (*matrix)[15] + (*matrix)[4]  * (*matrix)[11] * (*matrix)[14] + (*matrix)[8]  * (*matrix)[6]  * (*matrix)[15] - (*matrix)[8]  * (*matrix)[7]  * (*matrix)[14] - (*matrix)[12] * (*matrix)[6]  * (*matrix)[11] + (*matrix)[12] * (*matrix)[7]  * (*matrix)[10];
  (*inverseMatrix)[5] = (*matrix)[0]  * (*matrix)[10] * (*matrix)[15] - (*matrix)[0]  * (*matrix)[11] * (*matrix)[14] - (*matrix)[8]  * (*matrix)[2] * (*matrix)[15] + (*matrix)[8]  * (*matrix)[3] * (*matrix)[14] + (*matrix)[12] * (*matrix)[2] * (*matrix)[11] - (*matrix)[12] * (*matrix)[3] * (*matrix)[10];
  (*inverseMatrix)[6] = -(*matrix)[0]  * (*matrix)[6] * (*matrix)[15] + (*matrix)[0]  * (*matrix)[7] * (*matrix)[14] + (*matrix)[4]  * (*matrix)[2] * (*matrix)[15] - (*matrix)[4]  * (*matrix)[3] * (*matrix)[14] - (*matrix)[12] * (*matrix)[2] * (*matrix)[7] + (*matrix)[12] * (*matrix)[3] * (*matrix)[6];
  (*inverseMatrix)[7] = (*matrix)[0] * (*matrix)[6] * (*matrix)[11] - (*matrix)[0] * (*matrix)[7] * (*matrix)[10] - (*matrix)[4] * (*matrix)[2] * (*matrix)[11] + (*matrix)[4] * (*matrix)[3] * (*matrix)[10] + (*matrix)[8] * (*matrix)[2] * (*matrix)[7] - (*matrix)[8] * (*matrix)[3] * (*matrix)[6];
  (*inverseMatrix)[8] = (*matrix)[4]  * (*matrix)[9] * (*matrix)[15] - (*matrix)[4]  * (*matrix)[11] * (*matrix)[13] - (*matrix)[8]  * (*matrix)[5] * (*matrix)[15] + (*matrix)[8]  * (*matrix)[7] * (*matrix)[13] + (*matrix)[12] * (*matrix)[5] * (*matrix)[11] - (*matrix)[12] * (*matrix)[7] * (*matrix)[9];
  (*inverseMatrix)[9] = -(*matrix)[0]  * (*matrix)[9] * (*matrix)[15] + (*matrix)[0]  * (*matrix)[11] * (*matrix)[13] + (*matrix)[8]  * (*matrix)[1] * (*matrix)[15] - (*matrix)[8]  * (*matrix)[3] * (*matrix)[13] - (*matrix)[12] * (*matrix)[1] * (*matrix)[11] + (*matrix)[12] * (*matrix)[3] * (*matrix)[9];
  (*inverseMatrix)[10] = (*matrix)[0]  * (*matrix)[5] * (*matrix)[15] - (*matrix)[0]  * (*matrix)[7] * (*matrix)[13] - (*matrix)[4]  * (*matrix)[1] * (*matrix)[15] + (*matrix)[4]  * (*matrix)[3] * (*matrix)[13] + (*matrix)[12] * (*matrix)[1] * (*matrix)[7] - (*matrix)[12] * (*matrix)[3] * (*matrix)[5];
  (*inverseMatrix)[11] = -(*matrix)[0] * (*matrix)[5] * (*matrix)[11] + (*matrix)[0] * (*matrix)[7] * (*matrix)[9] + (*matrix)[4] * (*matrix)[1] * (*matrix)[11] - (*matrix)[4] * (*matrix)[3] * (*matrix)[9] - (*matrix)[8] * (*matrix)[1] * (*matrix)[7] + (*matrix)[8] * (*matrix)[3] * (*matrix)[5];
  (*inverseMatrix)[12] = -(*matrix)[4]  * (*matrix)[9] * (*matrix)[14] + (*matrix)[4]  * (*matrix)[10] * (*matrix)[13] +(*matrix)[8]  * (*matrix)[5] * (*matrix)[14] - (*matrix)[8]  * (*matrix)[6] * (*matrix)[13] - (*matrix)[12] * (*matrix)[5] * (*matrix)[10] + (*matrix)[12] * (*matrix)[6] * (*matrix)[9];
  (*inverseMatrix)[13] = (*matrix)[0]  * (*matrix)[9] * (*matrix)[14] - (*matrix)[0]  * (*matrix)[10] * (*matrix)[13] - (*matrix)[8]  * (*matrix)[1] * (*matrix)[14] + (*matrix)[8]  * (*matrix)[2] * (*matrix)[13] + (*matrix)[12] * (*matrix)[1] * (*matrix)[10] - (*matrix)[12] * (*matrix)[2] * (*matrix)[9];
  (*inverseMatrix)[14] = -(*matrix)[0]  * (*matrix)[5] * (*matrix)[14] + (*matrix)[0]  * (*matrix)[6] * (*matrix)[13] + (*matrix)[4]  * (*matrix)[1] * (*matrix)[14] - (*matrix)[4]  * (*matrix)[2] * (*matrix)[13] - (*matrix)[12] * (*matrix)[1] * (*matrix)[6] + (*matrix)[12] * (*matrix)[2] * (*matrix)[5];
  (*inverseMatrix)[15] = (*matrix)[0] * (*matrix)[5] * (*matrix)[10] - (*matrix)[0] * (*matrix)[6] * (*matrix)[9] - (*matrix)[4] * (*matrix)[1] * (*matrix)[10] + (*matrix)[4] * (*matrix)[2] * (*matrix)[9] + (*matrix)[8] * (*matrix)[1] * (*matrix)[6] - (*matrix)[8] * (*matrix)[2] * (*matrix)[5];

  float determinant = 1.0 / ((*matrix)[0] * (*inverseMatrix)[0] + (*matrix)[1] * (*inverseMatrix)[4] + (*matrix)[2] * (*inverseMatrix)[8] + (*matrix)[3] * (*inverseMatrix)[12]);
  
  for (int x = 0; x < 16; x++) { 
    (*inverseMatrix)[x] *= determinant; 
  }

  return inverseMatrix; 
}