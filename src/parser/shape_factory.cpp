#include "shape_factory.h"

Shape* ShapeGenerator::create() {
  return new Shape(nullptr, nullptr);
}

Shape* SphereGenerator::create() {
  return new Sphere(nullptr, nullptr);
}

std::map<std::string, ShapeGenerator*> ShapeFactory::stringShapeGeneratorMap = {
  {"Sphere", new SphereGenerator()}
};

Shape* ShapeFactory::generateShapeFromString(std::string word) {
  return stringShapeGeneratorMap[word]->create();
}