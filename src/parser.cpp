#include "parser.h"
#include <stdio.h>

std::string RST::toString() {
  std::string printOut = "RST";
  return printOut;
}

std::string ShapeRST::toString() {
  std::string printOut = "ShapeRST: ";
  printOut += type + " -> " + identifier;
  return printOut;
}

std::string PropertyRST::toString() {
  std::string printOut = "PropertyRST: ";
  printOut += identifier + " -> [";
  for (int x = 0; x < dataList.size(); x++) {
    printOut += dataList[x];
    if (x == dataList.size() - 1) {
      printOut += "]";
    }
    else {
      printOut += ", ";
    }
  }

  return printOut;
}

std::string StructureRST::toString() {
  std::string printOut = "StructureRST";
  return printOut;
}

std::string WorldRST::toString() {
  std::string printOut = "WorldRST";
  return printOut;
}

std::string BlockRST::toString() {
  std::string printOut = "BlockRST";
  return printOut;
}


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

  RST* rootTree = parseWorld();
  printTree(rootTree, 0);

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
    if (!std::isalnum((*currentToken)[x]) && ((*currentToken)[x] != '.')) {
      return TokenType::Terminal;
    }

    if (std::isalpha((*currentToken)[x]) && ((*currentToken)[x] != '.')) {
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

void Parser::printTree(RST* root, int offset) {
  std::string offsetString(offset, ' ');
  printf("%s%s\n", offsetString.c_str(), root->toString().c_str());
  for (int x = 0; x < root->childrenList.size(); x++) {
    printTree(root->childrenList[x], offset + 2);
  }
}

RST* Parser::parseWorld() {
  RST* tree = new WorldRST;

  nextToken();
  expectToken("World");
  tree->childrenList.push_back(parseBlock());

  return tree;
}

RST* Parser::parseBlock() {
  RST* tree = new BlockRST;

  nextToken();
  expectToken("{");
  nextToken();
  while (checkTokenType() == TokenType::Type) {
    tree->childrenList.push_back(parseShape());
  }
  expectToken("}");

  return tree;
}

RST* Parser::parseShape() {
  RST* tree = new ShapeRST;

  ((ShapeRST*)tree)->type = *currentToken;
  nextToken();
  expectIdentifier();
  ((ShapeRST*)tree)->identifier = *currentToken;
  tree->childrenList.push_back(parseStructure());

  return tree;
}

RST* Parser::parseStructure() {
  RST* tree = new StructureRST;

  nextToken();
  expectToken("{");
  nextToken();

  while (checkTokenType() == TokenType::Type) {
    tree->childrenList.push_back(parseProperty());
  }

  expectToken("}");
  nextToken();

  return tree;
}

RST* Parser::parseProperty() {
  RST* tree = new PropertyRST;

  std::string identifier = *currentToken;
  ((PropertyRST*)tree)->identifier = *currentToken;
  nextToken();
  expectToken("=");
  nextToken();

  if (checkTokenType() == TokenType::Constant) {
    ((PropertyRST*)tree)->dataList.push_back(*currentToken);
    nextToken();
  }
  else {
    expectToken("[");
    nextToken();

    while (checkTokenType() == TokenType::Constant) {
      ((PropertyRST*)tree)->dataList.push_back(*currentToken);
      nextToken();
    }

    expectToken("]");
    nextToken();
  }

  return tree;
}