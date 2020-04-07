#include "scene.h"

Scene::Scene() {
  
}

Scene::~Scene() {
  for (int x = 0; x < cameraList.size(); x++) {
    delete cameraList[x];
  }
  for (int x = 0; x < shapeList.size(); x++) {
    delete shapeList[x];
  }
}

void Scene::addCamera(Camera* camera) {
  cameraList.push_back(camera);
}

void Scene::addShape(Shape* shape) {
  shapeList.push_back(shape);
}

char* Scene::render(Vector2 resolution) {
  return nullptr;
}