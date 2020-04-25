#pragma once
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
  virtual void computeScatteringFunctions(SurfaceInteraction* surfaceInteraction, MemoryArea* area, TransportMode mode, bool allowMultipleLobes);
};