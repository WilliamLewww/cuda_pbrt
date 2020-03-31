#pragma once
#include "transformation_matrix.h"

class Shape {
private:
  TransformationMatrix* objectToWorld;
  TransformationMatrix* worldToObject;
public:
  Shape(TransformationMatrix* objectToWorld, TransformationMatrix* worldToObject);
  ~Shape();
};