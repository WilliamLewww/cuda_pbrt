#include "parser.h"

int main(int argn, const char** argv) {
  const char* filename = argv[1];

  Parser* parser = new Parser();
  Scene* scene = parser->createSceneFromFile(filename);
  char* image = scene->render();

  delete image;
  delete scene;
  delete parser;

  return 0;
}