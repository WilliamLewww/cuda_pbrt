#pragma once
#include <vector>

#include "vector.h"
#include "shape.h"
#include "camera.h"
#include "sphere.h"

class Scene {
private:
  std::vector<Camera*> cameraList;
  std::vector<Shape*> shapeList;
public:
  Scene();
  ~Scene();

  void addCamera(Camera* camera);
  void addShape(Shape* shape);

  Vector4 getRayIntersection(Ray* ray);
  Vector4* render(Vector2 resolution);
};