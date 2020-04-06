#pragma once
#include <vector>
#include "shape.h"

class Scene {
private:
  std::vector<Shape*> shapeList;
public:
  Scene();
  ~Scene();

  void addShape(Shape* shape);

  char* render(int resolutionWidth, int resolutionHeight);
};