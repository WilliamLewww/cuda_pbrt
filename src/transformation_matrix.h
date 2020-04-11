#pragma once
#include "matrix.h"
#include "bounds.h"

class TransformationMatrix {
private:
  Matrix4x4* matrix;
  Matrix4x4* inverseMatrix;
public:
  TransformationMatrix();
  TransformationMatrix(Matrix4x4* matrix);
  ~TransformationMatrix();

  Matrix4x4* getMatrix();
  Matrix4x4* getInverseMatrix();

  void setMatrix(Matrix4x4* matrix);

  Vector3 operator()(Vector3 b);
  Bounds3 operator()(Bounds3 b);
};