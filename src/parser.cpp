#include "parser.h"
#include <stdio.h>

Parser::Parser() {

}

Parser::~Parser() {

}

Scene* Parser::createSceneFromFile(const char* filename) {
  printf("%s\n", filename);
  return nullptr;
}