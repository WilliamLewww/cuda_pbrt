#include "shape_factory.h"

Shape* ShapeGenerator::create() {
  return new Shape();
}

Shape* SphereGenerator::create() {
  return new Sphere();
}

std::map<std::string, ShapeGenerator*> ShapeFactory::stringShapeGeneratorMap = {
  {"Sphere", new SphereGenerator()}
};

Shape* ShapeFactory::generateShapeFromString(std::string word) {
  return stringShapeGeneratorMap[word]->create();
}