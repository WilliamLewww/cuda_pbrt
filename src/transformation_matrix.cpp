#include "transformation_matrix.h"

TransformationMatrix::TransformationMatrix() {
  matrix = createIdentityMatrix4x4();
  inverseMatrix = createIdentityMatrix4x4();
}

TransformationMatrix::TransformationMatrix(Matrix4x4* matrix) {
  this->matrix = matrix;
}

TransformationMatrix::~TransformationMatrix() {
  delete matrix;
  delete inverseMatrix;
}