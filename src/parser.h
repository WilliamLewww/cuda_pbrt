#pragma once
#include <fstream>
#include <string>
#include "scene.h"

struct RST {
  std::vector<RST*> childrenList;
};

struct WorldRST : RST {
  std::string identifier;
};

class Parser {
private:
  std::fstream* file;
  std::string* currentToken;

  bool nextToken();
  void expectToken(std::string token);
  void expectIdentifier();

  RST* ParseWorld();
public:
  Parser();
  ~Parser();

  Scene* createSceneFromFile(const char* filename);
};