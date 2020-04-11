#pragma once
#include "transformation_matrix.h"
#include "bounds.h"

class Shape {
private:
  TransformationMatrix* objectToWorld;
  TransformationMatrix* worldToObject;
public:
  Shape();
  Shape(TransformationMatrix* objectToWorld, TransformationMatrix* worldToObject);
  ~Shape();

  void setTransformationMatrix(TransformationMatrix* objectToWorld, TransformationMatrix* worldToObject);

  TransformationMatrix* getObjectToWorld();

  virtual Bounds3 objectBounds();
  Bounds3 worldBounds();
};