#include "scene.h"

Scene::Scene(Primitive* aggregate) {
  this->aggregate = aggregate;

  worldBounds = aggregate->worldBounds();
}

Scene::~Scene() {
  
}

Bounds3 Scene::getWorldBounds() {
  return worldBounds;
}

bool Scene::checkRayIntersectionPredicate(Ray* ray) {
  return aggregate->checkRayIntersectionPredicate(ray);
}

bool Scene::checkRayIntersection(Ray* ray, SurfaceInteraction* surfaceInteraction) {
  return aggregate->checkRayIntersection(ray, surfaceInteraction);
}