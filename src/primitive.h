#pragma once
#include "shape.h"
#include "bounds.h"
#include "ray.h"
#include "interaction.h"
#include "memory_area.h"

enum class TransportMode {
  Radiance, Importance
};

class Primitive {
public:
  virtual Bounds3 worldBounds();
  virtual bool checkRayIntersection(Ray* ray, SurfaceInteraction* surfaceInteraction);
};

class GeometricPrimitive : public Primitive {
private:
  Shape* shape;
public:
  GeometricPrimitive(Shape* shape);
  ~GeometricPrimitive();

  Bounds3 worldBounds();
  bool checkRayIntersection(Ray* ray, SurfaceInteraction* surfaceInteraction);
};

class Aggregate : public Primitive {};