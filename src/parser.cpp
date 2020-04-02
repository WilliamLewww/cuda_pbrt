#include "parser.h"

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

bool Parser::nextWord() {
  if (*file >> *currentWord) {
    return true;
  }

  return false;
}

void Parser::expectToken(Token token) {
  if (TokenGenerator::stringTokenMap[*currentWord] != token) {
    throw;
  }
}

void Parser::expectIdentifier() {
  if (TokenGenerator::getTokenFromWord(*currentWord) != TokenType::Identifier) {
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

  nextWord();
  expectToken(Token::World);
  tree->childrenList.push_back(parseBlock());

  return tree;
}

RST* Parser::parseBlock() {
  RST* tree = new BlockRST;

  nextWord();
  expectToken(Token::OpenCurlyBracket);
  nextWord();
  while (TokenGenerator::getTokenFromWord(*currentWord) == TokenType::Type) {
    tree->childrenList.push_back(parseShape());
  }
  expectToken(Token::CloseCurlyBracket);

  return tree;
}

RST* Parser::parseShape() {
  RST* tree = new ShapeRST;

  ((ShapeRST*)tree)->type = *currentWord;
  nextWord();
  expectIdentifier();
  ((ShapeRST*)tree)->identifier = *currentWord;
  tree->childrenList.push_back(parseStructure());

  return tree;
}

RST* Parser::parseStructure() {
  RST* tree = new StructureRST;

  nextWord();
  expectToken(Token::OpenCurlyBracket);
  nextWord();

  while (TokenGenerator::getTokenFromWord(*currentWord) == TokenType::Type) {
    tree->childrenList.push_back(parseProperty());
  }

  expectToken(Token::CloseCurlyBracket);
  nextWord();

  return tree;
}

RST* Parser::parseProperty() {
  RST* tree = new PropertyRST;

  std::string identifier = *currentWord;
  ((PropertyRST*)tree)->identifier = *currentWord;
  nextWord();
  expectToken(Token::Equals);
  nextWord();

  if (TokenGenerator::getTokenFromWord(*currentWord) == TokenType::Constant) {
    ((PropertyRST*)tree)->dataList.push_back(*currentWord);
    nextWord();
  }
  else {
    expectToken(Token::OpenSquareBracket);
    nextWord();

    while (TokenGenerator::getTokenFromWord(*currentWord) == TokenType::Constant) {
      ((PropertyRST*)tree)->dataList.push_back(*currentWord);
      nextWord();
    }

    expectToken(Token::CloseSquareBracket);
    nextWord();
  }

  return tree;
}