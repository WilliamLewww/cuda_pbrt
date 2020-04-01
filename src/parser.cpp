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

TokenType Parser::checkTokenType() {
  bool isConstant = true;

  int x = 0;
  while (x < currentToken->length()) {
    if (!std::isalnum((*currentToken)[x])) {
      return TokenType::Terminal;
    }
    if (std::isalpha((*currentToken)[x]) || (*currentToken)[x] == '.') {
      isConstant = false;
    }

    x++;
  }

  if (isConstant) {
    return TokenType::Constant;
  }

  if (std::isupper((*currentToken)[0])) {
    return TokenType::Type;
  }

  return TokenType::Identifier;
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
  tree->childrenList.push_back(ParseBlock());

  return tree;
}

RST* Parser::ParseBlock() {
  RST* tree = new BlockRST;

  nextToken();
  expectToken("{");
  nextToken();
  while (checkTokenType() == TokenType::Type) {
    tree->childrenList.push_back(ParseShape());
  }
  expectToken("}");

  return tree;
}

RST* Parser::ParseShape() {
  RST* tree = new ShapeRST;

  ((ShapeRST*)tree)->type = new std::string(*currentToken);
  nextToken();
  expectIdentifier();
  ((ShapeRST*)tree)->identifier = new std::string(*currentToken);
  tree->childrenList.push_back(ParseStructure());

  return tree;
}

RST* Parser::ParseStructure() {
  RST* tree = new StructureRST;

  nextToken();
  expectToken("{");
  nextToken();

  while (checkTokenType() == TokenType::Type) {
    std::string identifier = *currentToken;
    ((StructureRST*)tree)->dataMap.insert(std::make_pair(identifier, new std::vector<std::string>));
    nextToken();
    expectToken("=");
    nextToken();

    if (checkTokenType() == TokenType::Constant) {
      ((StructureRST*)tree)->dataMap[identifier]->push_back(*currentToken);
      nextToken();
    }
    else {

    }
  }

  expectToken("}");
  nextToken();

  return tree;
}