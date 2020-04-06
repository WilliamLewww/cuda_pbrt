#pragma once
#include <fstream>
#include <map>
#include <stdio.h>
#include <string>

#include "../scene.h"
#include "parser_memory.h"
#include "rst.h"
#include "shape_factory.h"
#include "token.h"

class Parser {
private:
  std::fstream* file;
  std::string* currentWord;

  void deleteTree(RST* root);
  void parseTree(RST* root, ParserMemory* memory);
  void printTree(RST* root, int offset = 0);

  bool nextWord();

  void expectToken(Token token);
  void expectIdentifier();

  RST* parseWorld();
  RST* parseBlock();
  RST* parseShape();
  RST* parseStructure();
  RST* parseProperty();
public:
  Parser();
  ~Parser();

  Scene* createSceneFromFile(const char* filename);
};