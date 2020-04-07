#include "scene.h"

Scene::Scene() {
  
}

Scene::~Scene() {
  for (int x = 0; x < shapeList.size(); x++) {
    delete shapeList[x];
  }

  shapeList.clear();
}

void Scene::addShape(Shape* shape) {
  shapeList.push_back(shape);
}

char* Scene::render(Vector2 resolution) {
  return nullptr;
}