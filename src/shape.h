#pragma once
#include "transformation_matrix.h"
#include "bounds.h"
#include "interaction.h"

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

  Bounds3 worldBounds();

  virtual Bounds3 objectBounds();
  virtual bool checkRayIntersection(Ray* ray, float* firstHit, SurfaceInteraction* surfaceInteraction, bool testAlphaTexture = true);
};