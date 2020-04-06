#pragma once
#include <vector>

#include "vector.h"
#include "shape.h"

class Scene {
private:
  std::vector<Shape*> shapeList;
public:
  Scene();
  ~Scene();

  void addShape(Shape* shape);

  char* render(Vector2 resolution);
};