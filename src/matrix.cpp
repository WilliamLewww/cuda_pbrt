#include "matrix.h"

float& Matrix4x4::operator[](int x) {
  return this->data[x];
}

void printMatrix4x4(Matrix4x4* matrix) {
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      printf("%f ", (*matrix)[y * 4 + x]);
    }
    printf("\n");
  }
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

Matrix4x4* multiplyMatrix4x4(Matrix4x4* a, Matrix4x4* b) {
  Matrix4x4* matrix = new Matrix4x4;
  (*matrix)[0] = ((*a)[0] * (*b)[0]) + ((*a)[1] * (*b)[4]) + ((*a)[2] * (*b)[8]) + ((*a)[3] * (*b)[12]);
  (*matrix)[1] = ((*a)[0] * (*b)[1]) + ((*a)[1] * (*b)[5]) + ((*a)[2] * (*b)[9]) + ((*a)[3] * (*b)[13]);
  (*matrix)[2] = ((*a)[0] * (*b)[2]) + ((*a)[1] * (*b)[6]) + ((*a)[2] * (*b)[10]) + ((*a)[3] * (*b)[14]);
  (*matrix)[3] = ((*a)[0] * (*b)[3]) + ((*a)[1] * (*b)[7]) + ((*a)[2] * (*b)[11]) + ((*a)[3] * (*b)[15]);
  (*matrix)[4] = ((*a)[4] * (*b)[0]) + ((*a)[5] * (*b)[4]) + ((*a)[6] * (*b)[8]) + ((*a)[7] * (*b)[12]);
  (*matrix)[5] = ((*a)[4] * (*b)[1]) + ((*a)[5] * (*b)[5]) + ((*a)[6] * (*b)[9]) + ((*a)[7] * (*b)[13]);
  (*matrix)[6] = ((*a)[4] * (*b)[2]) + ((*a)[5] * (*b)[6]) + ((*a)[6] * (*b)[10]) + ((*a)[7] * (*b)[14]);
  (*matrix)[7] = ((*a)[4] * (*b)[3]) + ((*a)[5] * (*b)[7]) + ((*a)[6] * (*b)[11]) + ((*a)[7] * (*b)[15]);
  (*matrix)[8] = ((*a)[8] * (*b)[0]) + ((*a)[9] * (*b)[4]) + ((*a)[10] * (*b)[8]) + ((*a)[11] * (*b)[12]);
  (*matrix)[9] = ((*a)[8] * (*b)[1]) + ((*a)[9] * (*b)[5]) + ((*a)[10] * (*b)[9]) + ((*a)[11] * (*b)[13]);
  (*matrix)[10] = ((*a)[8] * (*b)[2]) + ((*a)[9] * (*b)[6]) + ((*a)[10] * (*b)[10]) + ((*a)[11] * (*b)[14]);
  (*matrix)[11] = ((*a)[8] * (*b)[3]) + ((*a)[9] * (*b)[7]) + ((*a)[10] * (*b)[11]) + ((*a)[11] * (*b)[15]);
  (*matrix)[12] = ((*a)[12] * (*b)[0]) + ((*a)[13] * (*b)[4]) + ((*a)[14] * (*b)[8]) + ((*a)[15] * (*b)[12]);
  (*matrix)[13] = ((*a)[12] * (*b)[1]) + ((*a)[13] * (*b)[5]) + ((*a)[14] * (*b)[9]) + ((*a)[15] * (*b)[13]);
  (*matrix)[14] = ((*a)[12] * (*b)[2]) + ((*a)[13] * (*b)[6]) + ((*a)[14] * (*b)[10]) + ((*a)[15] * (*b)[14]);
  (*matrix)[15] = ((*a)[12] * (*b)[3]) + ((*a)[13] * (*b)[7]) + ((*a)[14] * (*b)[11]) + ((*a)[15] * (*b)[15]);

  return matrix;
}

Matrix4x4* createIdentityMatrix4x4() {
  Matrix4x4* matrix = new Matrix4x4;
  (*matrix)[0] = 1.0;  (*matrix)[1] = 0.0;  (*matrix)[2] = 0.0;  (*matrix)[3] = 0.0;
  (*matrix)[4] = 0.0;  (*matrix)[5] = 1.0;  (*matrix)[6] = 0.0;  (*matrix)[7] = 0.0;
  (*matrix)[8] = 0.0;  (*matrix)[9] = 0.0;  (*matrix)[10] = 1.0; (*matrix)[11] = 0.0;
  (*matrix)[12] = 0.0; (*matrix)[13] = 0.0; (*matrix)[14] = 0.0; (*matrix)[15] = 1.0;

  return matrix;
}

Matrix4x4* createTranslateMatrix4x4(Vector3 position) {
  Matrix4x4* matrix = new Matrix4x4;
  (*matrix)[0] = 1.0;  (*matrix)[1] = 0.0;  (*matrix)[2] = 0.0;  (*matrix)[3] = position[0];
  (*matrix)[4] = 0.0;  (*matrix)[5] = 1.0;  (*matrix)[6] = 0.0;  (*matrix)[7] = position[1];
  (*matrix)[8] = 0.0;  (*matrix)[9] = 0.0;  (*matrix)[10] = 1.0; (*matrix)[11] = position[2];
  (*matrix)[12] = 0.0; (*matrix)[13] = 0.0; (*matrix)[14] = 0.0; (*matrix)[15] = 1.0;

  return matrix;
}