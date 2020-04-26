#include "primitive.h"

Bounds3 Primitive::worldBounds() {}
bool Primitive::checkRayIntersection(Ray* ray, SurfaceInteraction* surfaceInteraction) {}

GeometricPrimitive::GeometricPrimitive(Shape* shape) {
  this->shape = shape;
}

GeometricPrimitive::~GeometricPrimitive() {

}

Bounds3 GeometricPrimitive::worldBounds() {
  return shape->worldBounds();
}

bool GeometricPrimitive::checkRayIntersection(Ray* ray, SurfaceInteraction* surfaceInteraction) {
  float tHit;
  if (!shape->checkRayIntersection(ray, &tHit, surfaceInteraction)) {
    return false;
  }

  ray->tMax = tHit;
  surfaceInteraction->primitive = this;
  return true;
}