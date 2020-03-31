#include "parser.h"
#include <stdio.h>

Parser::Parser() {
  file = new std::fstream;
  currentToken = new std::string;
}

Parser::~Parser() {
  delete currentToken;

  file->close();
  delete file;
}

Scene* Parser::createSceneFromFile(const char* filename) {
  Scene* scene = new Scene();
  file->open(filename);
  RST* rootTree;

  rootTree = ParseWorld();

  return nullptr;
}

bool Parser::nextToken() {
  if (*file >> *currentToken) {
    return true;
  }

  return false;
}

void Parser::expectToken(std::string token) {
  if (*currentToken != token) {
    throw;
  }
}

void Parser::expectIdentifier() {
  int x = 0;
  while (x < currentToken->length()) {
    if (!std::isalnum((*currentToken)[x])) {
      throw;
    }
    x++;
  }
}

RST* Parser::ParseWorld() {
  RST* tree = new WorldRST;
  
  nextToken();
  expectToken("World");
  nextToken();
  expectIdentifier();

  return tree;
}