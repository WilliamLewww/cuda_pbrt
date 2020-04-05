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
  ParserMemory* parserMemory = new ParserMemory();
  printTree(rootTree);
  parseTree(rootTree, parserMemory);
  parserMemory->linkAllShapeTransformationMatrix();

  return nullptr;
}

void Parser::parseTree(RST* root, ParserMemory* memory) {
  if (root->getTypeString() == "ShapeRST") {
    ShapeRST* rootCast = (ShapeRST*)root;

    memory->pushTransformationMatrix(new TransformationMatrix());
    memory->pushShape(ShapeFactory::generateShapeFromString(rootCast->type), rootCast->identifier);
    memory->mapLastShapeTransformationMatrix();
  }

  if (root->getTypeString() == "PropertyRST") {
    PropertyRST* rootCast = (PropertyRST*)root;

    if (rootCast->identifier == "Translate") {
      Vector3 position(std::stof(rootCast->dataList[0]), std::stof(rootCast->dataList[1]), std::stof(rootCast->dataList[2]));

      TransformationMatrix* transformationMatrix = memory->getLastTransformationMatrix();
      transformationMatrix->setMatrix(multiplyMatrix4x4(createTranslateMatrix4x4(position), transformationMatrix->getMatrix()));
    }
  }

  for (int x = 0; x < root->childrenList.size(); x++) {
    parseTree(root->childrenList[x], memory);
  }
}

void Parser::printTree(RST* root, int offset) {
  std::string offsetString(offset, ' ');
  printf("%s%s\n", offsetString.c_str(), root->toString().c_str());
  for (int x = 0; x < root->childrenList.size(); x++) {
    printTree(root->childrenList[x], offset + 2);
  }
}

bool Parser::nextWord() {
  if (*file >> *currentWord) {
    return true;
  }

  return false;
}

void Parser::expectToken(Token token) {
  if (TokenHelper::stringTokenMap[*currentWord] != token) {
    throw;
  }
}

void Parser::expectIdentifier() {
  if (TokenHelper::getTokenFromWord(*currentWord) != TokenType::Identifier) {
    throw;
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
  while (TokenHelper::getTokenFromWord(*currentWord) == TokenType::Type) {
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

  while (TokenHelper::getTokenFromWord(*currentWord) == TokenType::Type) {
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

  if (TokenHelper::getTokenFromWord(*currentWord) == TokenType::Constant) {
    ((PropertyRST*)tree)->dataList.push_back(*currentWord);
    nextWord();
  }
  else {
    expectToken(Token::OpenSquareBracket);
    nextWord();

    while (TokenHelper::getTokenFromWord(*currentWord) == TokenType::Constant) {
      ((PropertyRST*)tree)->dataList.push_back(*currentWord);
      nextWord();
    }

    expectToken(Token::CloseSquareBracket);
    nextWord();
  }

  return tree;
}