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

Vector4 TransformationMatrix::operator()(Vector4 b) {
  Vector4 vector(
    (*matrix)[0] * b[0] + (*matrix)[1] * b[1] + (*matrix)[2] * b[2] + (*matrix)[3] * b[3],
    (*matrix)[4] * b[0] + (*matrix)[5] * b[1] + (*matrix)[6] * b[2] + (*matrix)[7] * b[3],
    (*matrix)[8] * b[0] + (*matrix)[9] * b[1] + (*matrix)[10] * b[2] + (*matrix)[11] * b[3],
    (*matrix)[12] * b[0] + (*matrix)[13] * b[1] + (*matrix)[14] * b[2] + (*matrix)[15] * b[3]
  );

  return vector;
}

Bounds3 TransformationMatrix::operator()(Bounds3 b) {
  Bounds3 bounds((*this)(Vector4(b[0][0], b[0][1], b[0][2], 1)));
  bounds = bounds.getUnion((*this)(Vector4(b[1][0], b[0][1], b[0][2], 1)));
  bounds = bounds.getUnion((*this)(Vector4(b[0][0], b[1][1], b[0][2], 1)));
  bounds = bounds.getUnion((*this)(Vector4(b[0][0], b[0][1], b[1][2], 1)));
  bounds = bounds.getUnion((*this)(Vector4(b[0][0], b[1][1], b[1][2], 1)));
  bounds = bounds.getUnion((*this)(Vector4(b[1][0], b[1][1], b[0][2], 1)));
  bounds = bounds.getUnion((*this)(Vector4(b[1][0], b[0][1], b[1][2], 1)));
  bounds = bounds.getUnion((*this)(Vector4(b[1][0], b[1][1], b[1][2], 1)));

  return bounds;
}

Ray TransformationMatrix::operator()(Ray b) {
  Vector4 origin = (*this)(b.origin);
  Vector4 direction = (*this)(b.direction);

  return Ray(origin, direction, b.tMax, b.time);
}