#include "shell.h"

int main(int argn, const char** argv) {
  Shell* shell = new Shell(argn, argv);
  delete shell;

  // FileSystemDriver* fileSystem = new FileSystemDriver("dump/drive", 50, 512);
  // delete fileSystem;

  // Parser* parser = new Parser();
  // Scene* scene = parser->createSceneFromFile(filename);
  // Vector4* image = scene->render(Vector2(250, 250));

  // unsigned char* imageData = (unsigned char*)malloc(250*250*4*sizeof(unsigned char));
  // for (int x = 0; x < 250 * 250; x++) {
  //   imageData[(x * 4) + 0] = image[x][0];
  //   imageData[(x * 4) + 1] = image[x][1];
  //   imageData[(x * 4) + 2] = image[x][2];
  //   imageData[(x * 4) + 3] = image[x][3];
  // }

  // stbi_write_png("dump/image.png", 250, 250, 4, imageData, 250*4*sizeof(unsigned char));

  // delete image;
  // delete scene;
  // delete parser;

  return 0;
}