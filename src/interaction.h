#pragma once
#include "vector.h"
#include "ray.h"

class Shape;
class Primitive;

struct Interaction {
  Vector4 position;
  Vector4 normal;
  Vector4 direction;

  float time;
  Vector4 positionError;

  bool isSurfaceInteraction();
  Ray spawnRay(Vector4 direction);
  Ray spawnRayToPosition(Vector4 targetPosition);
};

struct InteractionShading {
  Vector4 normal;
  Vector4 dpdu, dpdv;
  Vector4 dndu, dndv;
};

class SurfaceInteraction : public Interaction {
public:
  Vector2 uv;
  Vector4 dpdu, dpdv;
  Vector4 dndu, dndv;

  Shape* shape;
  InteractionShading shading;

  Primitive* primitive;

  SurfaceInteraction();
  SurfaceInteraction(Vector4 position, Vector4 positionError, Vector2 uv, Vector4 direction, Vector4 dpdu, Vector4 dpdv, Vector4 dndu, Vector4 dndv, float time, Shape* shape);
};