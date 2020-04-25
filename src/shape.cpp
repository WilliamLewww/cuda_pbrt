#include "shape.h"

Bounds3 Shape::objectBounds() {}
bool Shape::checkRayIntersection(Ray* ray, float* firstHit, SurfaceInteraction* surfaceInteraction, bool testAlphaTexture) {}

Shape::Shape() {
  this->objectToWorld = nullptr;
  this->worldToObject = nullptr;
}

Shape::Shape(TransformationMatrix* objectToWorld, TransformationMatrix* worldToObject) {
  this->objectToWorld = objectToWorld;
  this->worldToObject = worldToObject;
}

Shape::~Shape() {

}

void Shape::setTransformationMatrix(TransformationMatrix* objectToWorld, TransformationMatrix* worldToObject) {
  this->objectToWorld = objectToWorld;
  this->worldToObject = worldToObject;
}

TransformationMatrix* Shape::getObjectToWorld() {
  return objectToWorld;
}

Bounds3 Shape::worldBounds() {
  return (*objectToWorld)(objectBounds());
}