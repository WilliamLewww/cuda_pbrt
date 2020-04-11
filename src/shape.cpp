#include "shape.h"

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

Bounds3 Shape::objectBounds() {
  return Bounds3();
}

Bounds3 Shape::worldBounds() {
  return (*objectToWorld)(objectBounds());
}