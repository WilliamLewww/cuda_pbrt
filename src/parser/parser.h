#pragma once
#include <stdio.h>
#include <fstream>
#include <string>
#include <map>

#include "parser_memory.h"
#include "token.h"
#include "rst.h"
#include "../scene.h"

class Parser {
private:
  std::fstream* file;
  std::string* currentWord;

  void parseTree(RST* root, ParserMemory* parserMemory);
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