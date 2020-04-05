#pragma once
#include <map>
#include <string>

#include "../shape.h"
#include "../sphere.h"
#include "../transformation_matrix.h"

class ShapeGenerator {
private:
  static std::map<std::string, Shape*> stringShapeMap;
public:
  static Shape* generateShapeFromString(std::string word);
};