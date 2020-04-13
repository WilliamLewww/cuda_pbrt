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

Vector4 Scene::getRayIntersection(Ray* ray) {
  Vector4 color = Vector4(0, 0, 0, 255);

  for (int shapeIndex = 0; shapeIndex < shapeList.size(); shapeIndex++) {
    float hit0, hit1;
    bool intersect = shapeList[shapeIndex]->worldBounds().checkRayIntersection(ray, &hit0, &hit1);

    if (intersect) {
      float shapeHit0;
      SurfaceInteraction surfaceInteraction;
      bool shapeIntersect = shapeList[shapeIndex]->checkRayIntersection(ray, &shapeHit0, &surfaceInteraction);

      if (shapeIntersect) {
        color = Vector4(255, 255, 255, 255);
      }
    }
  }

  return color;
}

Vector4* Scene::render(Vector2 resolution) {
  Vector4* image = (Vector4*)malloc(resolution[0] * resolution[1] * sizeof(Vector4));

  for (int y = 0; y < resolution[1]; y++) {
    for (int x = 0; x < resolution[0]; x++) {
      CameraSample sample = {
        Vector2(x, y),
        Vector2(resolution[0] / 2, resolution[1] / 2),
        0.0
      };

      Ray* ray = cameraList[0]->generateRay(sample);
      image[y * (int)resolution[0] + x] = getRayIntersection(ray);
    }
  }

  return image;
}