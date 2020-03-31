#pragma once
#include "scene.h"

class Parser {
private:
public:
  Parser();
  ~Parser();

  Scene* createSceneFromFile(const char* filename);
};