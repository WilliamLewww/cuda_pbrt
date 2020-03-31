#include "parser.h"
#include <stdio.h>

Parser::Parser() {

}

Parser::~Parser() {

}

Scene* Parser::createSceneFromFile(const char* filename) {
  Scene* scene = new Scene();

  printf("%s\n", filename);
  return nullptr;
}