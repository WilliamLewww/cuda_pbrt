#include "transformation_matrix.h"

TransformationMatrix::TransformationMatrix() {
  matrix = createIdentityMatrix4x4();
  inverseMatrix = createIdentityMatrix4x4();
}

TransformationMatrix::TransformationMatrix(Matrix4x4* matrix) {
  this->matrix = matrix;
  inverseMatrix = inverseMatrix4x4(matrix);
}

TransformationMatrix::~TransformationMatrix() {
  delete matrix;
  delete inverseMatrix;
}

Matrix4x4* TransformationMatrix::getMatrix() {
  return matrix;
}

Matrix4x4* TransformationMatrix::getInverseMatrix() {
  return inverseMatrix;
}

void TransformationMatrix::setMatrix(Matrix4x4* matrix) {
  delete this->matrix;
  delete inverseMatrix;

  this->matrix = matrix;
  inverseMatrix = inverseMatrix4x4(matrix);
}

Vector3 TransformationMatrix::operator()(Vector3 b) {
  Vector3 vector(
    (*matrix)[0] * b[0] + (*matrix)[1] * b[1] + (*matrix)[2] * b[2],
    (*matrix)[4] * b[0] + (*matrix)[5] * b[1] + (*matrix)[6] * b[2],
    (*matrix)[7] * b[0] + (*matrix)[9] * b[1] + (*matrix)[10] * b[2]
  );

  return vector;
}

Bounds3 TransformationMatrix::operator()(Bounds3 b) {
  Bounds3 bounds((*this)(Vector3(b[0][0], b[0][1], b[0][2])));
  bounds = bounds.getUnion((*this)(Vector3(b[1][0], b[0][1],b[0][2])));
  bounds = bounds.getUnion((*this)(Vector3(b[0][0], b[1][1],b[0][2])));
  bounds = bounds.getUnion((*this)(Vector3(b[0][0], b[0][1],b[1][2])));
  bounds = bounds.getUnion((*this)(Vector3(b[0][0], b[1][1],b[1][2])));
  bounds = bounds.getUnion((*this)(Vector3(b[1][0], b[1][1],b[0][2])));
  bounds = bounds.getUnion((*this)(Vector3(b[1][0], b[0][1],b[1][2])));
  bounds = bounds.getUnion((*this)(Vector3(b[1][0], b[1][1],b[1][2])));

  return bounds;
}