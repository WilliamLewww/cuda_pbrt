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

  Bounds3 objectBounds();

  bool checkRayIntersection(Ray* ray, float* firstHit, SurfaceInteraction* surfaceInteraction, bool testAlphaTexture = true);
  bool checkQuadratic(float a, float b, float c, float* firstHit, float* secondHit);
  bool checkQuadratic(ErrorFloat a, ErrorFloat b, ErrorFloat c, ErrorFloat* firstHit, ErrorFloat* secondHit);
};