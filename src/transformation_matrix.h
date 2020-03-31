#pragma once
#include "matrix.h"

class TransformationMatrix {
private:
  Matrix4x4* matrix;
  Matrix4x4* inverseMatrix;
public:
  TransformationMatrix();
  TransformationMatrix(Matrix4x4* matrix);
  
  ~TransformationMatrix();
};