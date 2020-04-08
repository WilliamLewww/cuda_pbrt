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
  for (int x = 0; x < resolution[0]; x++) {
    for (int y = 0; y < resolution[1]; y++) {
      CameraSample sample = { 
        Vector2(x, y),
        Vector2(resolution[0] / 2, resolution[1] / 2),
        0.0
      };

      Ray* ray = cameraList[0]->generateRay(sample);
    }
  }
  return nullptr;
}