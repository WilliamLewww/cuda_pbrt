#pragma once
#include <vector>

#include "vector.h"
#include "primitive.h"

class Scene {
private:
  Primitive* aggregate;
  Bounds3 worldBounds;
public:
  Scene(Primitive* aggregate);
  ~Scene();

  Bounds3 getWorldBounds();

  bool checkRayIntersectionPredicate(Ray* ray);
  bool checkRayIntersection(Ray* ray, SurfaceInteraction* surfaceInteraction);
};