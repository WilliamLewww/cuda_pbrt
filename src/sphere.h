#pragma once
#include "shape.h"

class Sphere : public Shape {
private:
public:
  Sphere(TransformationMatrix* objectToWorld, TransformationMatrix* worldToObject);
  ~Sphere();
};