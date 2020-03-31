#include "scene.h"

int main(int argn, const char** argv) {
  const char* filename = argv[1];

  Scene* scene = new Scene(filename);
  scene->render();
  delete(scene);
  
  return 0;
}