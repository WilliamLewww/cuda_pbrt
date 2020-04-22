#pragma once
#include <map>
#include <string>

#include "../shape.h"
#include "../sphere.h"
#include "../transformation_matrix.h"

class ShapeGenerator {
public:
  virtual Shape* create();
};

class SphereGenerator : public ShapeGenerator {
public:
  virtual Shape* create();
};

class ShapeFactory {
private:
  static std::map<std::string, ShapeGenerator*> stringShapeGeneratorMap;
public:
  static Shape* generateShapeFromString(std::string word);
};