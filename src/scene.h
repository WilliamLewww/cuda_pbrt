#pragma once
#include <vector>

#include "vector.h"
#include "shape.h"
#include "camera.h"

class Scene {
private:
  std::vector<Camera*> cameraList;
  std::vector<Shape*> shapeList;
public:
  Scene();
  ~Scene();

  void addCamera(Camera* camera);
  void addShape(Shape* shape);

  char intersect(Ray* ray);
  char* render(Vector2 resolution);
};