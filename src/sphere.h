#pragma once
#include "shape.h"

class Sphere : public Shape {
private:
  float radius;
  float zMin, zMax;
  float thetaMin, thetaMax, phiMax;
public:
  Sphere();
  Sphere(TransformationMatrix* objectToWorld, TransformationMatrix* worldToObject, float radius, float zMin, float zMax, float phiMax);
  ~Sphere();

  void setConstructorDataMembers(float radius, float zMin, float zMax, float phiMax);
};