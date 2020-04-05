#include "shape_generator.h"

std::map<std::string, Shape*> ShapeGenerator::stringShapeMap = {
  {"Sphere", new Sphere(nullptr, nullptr)}
};

Shape* ShapeGenerator::generateShapeFromString(std::string word) {
  return stringShapeMap[word];
}