#include "shape.h"

Shape::Shape(TransformationMatrix* objectToWorld, TransformationMatrix* worldToObject) {
  this->objectToWorld = objectToWorld;
  this->worldToObject = worldToObject;
}

Shape::~Shape() {

}