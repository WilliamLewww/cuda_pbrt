#include "parser.h"
#include <stdio.h>

std::map<std::string, Token> Parser::stringTokenMap = {
  {"World", Token::World}, {"Camera", Token::Camera}, {"Sphere", Token::Sphere}, {"Radius", Token::Radius}, {"Translate", Token::Translate},
  {"Rotate", Token::Rotate}, {"Scale", Token::Scale}, {"=", Token::Equals}, {"{", Token::OpenCurlyBracket}, {"}", Token::CloseCurlyBracket}, 
  {"[", Token::OpenSquareBracket}, {"]", Token::CloseSquareBracket}
};

std::map<Token, TokenType> Parser::tokenTypeMap = {
  {Token::World, TokenType::Type}, {Token::Camera, TokenType::Type}, {Token::Sphere, TokenType::Type}, {Token::Radius, TokenType::Type},
  {Token::Translate, TokenType::Type}, {Token::Rotate, TokenType::Type}, {Token::Scale, TokenType::Type}, {Token::Equals, TokenType::Terminal}, 
  {Token::OpenCurlyBracket, TokenType::Terminal}, {Token::CloseCurlyBracket, TokenType::Terminal}, {Token::OpenSquareBracket, TokenType::Terminal}, 
  {Token::CloseSquareBracket, TokenType::Terminal}
};

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
  currentWord = new std::string;
}

Parser::~Parser() {
  delete currentWord;

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
  if (*file >> *currentWord) {
    return true;
  }

  return false;
}

TokenType Parser::checkTokenType() {
  if (stringTokenMap.find(*currentWord) != stringTokenMap.end()) {
    return tokenTypeMap[stringTokenMap[*currentWord]];
  }
  else {
    for (int x = 0; x < currentWord->length(); x++) {
      if (std::isalpha((*currentWord)[x])) {
        return TokenType::Identifier;
      }
    }
  }

  return TokenType::Constant;
}

void Parser::expectToken(Token token) {
  if (stringTokenMap[*currentWord] != token) {
    throw;
  }
}

void Parser::expectIdentifier() {
  if (checkTokenType() != TokenType::Identifier) {
    throw;
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
  expectToken(Token::World);
  tree->childrenList.push_back(parseBlock());

  return tree;
}

RST* Parser::parseBlock() {
  RST* tree = new BlockRST;

  nextToken();
  expectToken(Token::OpenCurlyBracket);
  nextToken();
  while (checkTokenType() == TokenType::Type) {
    tree->childrenList.push_back(parseShape());
  }
  expectToken(Token::CloseCurlyBracket);

  return tree;
}

RST* Parser::parseShape() {
  RST* tree = new ShapeRST;

  ((ShapeRST*)tree)->type = *currentWord;
  nextToken();
  expectIdentifier();
  ((ShapeRST*)tree)->identifier = *currentWord;
  tree->childrenList.push_back(parseStructure());

  return tree;
}

RST* Parser::parseStructure() {
  RST* tree = new StructureRST;

  nextToken();
  expectToken(Token::OpenCurlyBracket);
  nextToken();

  while (checkTokenType() == TokenType::Type) {
    tree->childrenList.push_back(parseProperty());
  }

  expectToken(Token::CloseCurlyBracket);
  nextToken();

  return tree;
}

RST* Parser::parseProperty() {
  RST* tree = new PropertyRST;

  std::string identifier = *currentWord;
  ((PropertyRST*)tree)->identifier = *currentWord;
  nextToken();
  expectToken(Token::Equals);
  nextToken();

  if (checkTokenType() == TokenType::Constant) {
    ((PropertyRST*)tree)->dataList.push_back(*currentWord);
    nextToken();
  }
  else {
    expectToken(Token::OpenSquareBracket);
    nextToken();

    while (checkTokenType() == TokenType::Constant) {
      ((PropertyRST*)tree)->dataList.push_back(*currentWord);
      nextToken();
    }

    expectToken(Token::CloseSquareBracket);
    nextToken();
  }

  return tree;
}