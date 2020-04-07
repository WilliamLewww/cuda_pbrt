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
  file->open(filename);

  RST* rootTree = parseWorld();
  ParserMemory* parserMemory = new ParserMemory();
  printTree(rootTree);
  parseTree(rootTree, parserMemory);
  parserMemory->linkAllShapeTransformationMatrix();
  parserMemory->linkAllCameraTransformationMatrix();

  Scene* scene = parserMemory->createScene();
  delete parserMemory;
  deleteTree(rootTree);

  return scene;
}

void Parser::deleteTree(RST* root) {
  for (int x = 0; x < root->childrenList.size(); x++) {
    deleteTree(root->childrenList[x]);
  }

  delete root;
}

void Parser::parseTree(RST* root, ParserMemory* memory) {
  if (root->getTypeString() == "ShapeRST") {
    ShapeRST* rootCast = (ShapeRST*)root;

    memory->pushTransformationMatrix(new TransformationMatrix());
    memory->pushShape(ShapeFactory::generateShapeFromString(rootCast->type), rootCast->identifier);
    memory->mapLastShapeTransformationMatrix();
  }

  if (root->getTypeString() == "CameraRST") {
    CameraRST* rootCast = (CameraRST*)root;

    memory->pushTransformationMatrix(new TransformationMatrix());
    memory->pushCamera(CameraFactory::generateCameraFromString(rootCast->type), rootCast->identifier);
    memory->mapLastCameraTransformationMatrix();
  }

  if (root->getTypeString() == "FunctionRST") {
    FunctionRST* rootCast = (FunctionRST*)root;

    memory->setCurrentFunctionFromString(rootCast->identifier);
  }

  if (root->getTypeString() == "PropertyRST") {
    PropertyRST* rootCast = (PropertyRST*)root;

    if (memory->getCurrentFunction() != Function::None) {
      Property property = { rootCast->identifier, rootCast->dataList };
      memory->pushProperty(property);

      if (memory->checkPropertyStackFull()) {
        parseFunctionStack(memory);
      }
    }
  }

  for (int x = 0; x < root->childrenList.size(); x++) {
    parseTree(root->childrenList[x], memory);
  }
}

void Parser::parseFunctionStack(ParserMemory* memory) {
  std::vector<Property> propertyList;

  while (!memory->checkPropertyStackEmpty()) {
    propertyList.push_back(memory->getPropertyStackTop());
    memory->popProperty();
  }

  if (memory->getCurrentFunction() == Function::Translate) {
    Vector3 position(std::stof(propertyList[0].dataList[0]), std::stof(propertyList[0].dataList[1]), std::stof(propertyList[0].dataList[2]));
  
    TransformationMatrix* transformationMatrix = memory->getLastTransformationMatrix();
    transformationMatrix->setMatrix(multiplyMatrix4x4(createTranslateMatrix4x4(position), transformationMatrix->getMatrix()));
  }

  if (memory->getCurrentFunction() == Function::Scale) {
    Vector3 size(std::stof(propertyList[0].dataList[0]), std::stof(propertyList[0].dataList[1]), std::stof(propertyList[0].dataList[2]));
  
    TransformationMatrix* transformationMatrix = memory->getLastTransformationMatrix();
    transformationMatrix->setMatrix(multiplyMatrix4x4(createScaleMatrix4x4(size), transformationMatrix->getMatrix()));
  }

  if (memory->getCurrentFunction() == Function::LookAt) {
    Vector3 position(std::stof(propertyList[2].dataList[0]), std::stof(propertyList[2].dataList[1]), std::stof(propertyList[2].dataList[2]));
    Vector3 target(std::stof(propertyList[1].dataList[0]), std::stof(propertyList[1].dataList[1]), std::stof(propertyList[1].dataList[2]));
    Vector3 up(std::stof(propertyList[0].dataList[0]), std::stof(propertyList[0].dataList[1]), std::stof(propertyList[0].dataList[2]));

    TransformationMatrix* transformationMatrix = memory->getLastTransformationMatrix();
    transformationMatrix->setMatrix(multiplyMatrix4x4(createLookAtMatrix4x4(position, target, up), transformationMatrix->getMatrix()));
  }

  memory->setCurrentFunctionFromString("None");
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
  if (TokenHelper::getTokenTypeFromString(*currentWord) != TokenType::Identifier) {
    throw;
  }
}

RST* Parser::parseWorld() {
  WorldRST* tree = new WorldRST;

  nextWord();
  expectToken(Token::World);

  nextWord();
  expectToken(Token::OpenCurlyBracket);
  nextWord();
  while (TokenHelper::getTokenTypeFromString(*currentWord) == TokenType::Type) {
    if (TokenHelper::getTokenBaseFromString(*currentWord) == Token::Camera) {
      tree->childrenList.push_back(parseCamera());
    }

    if (TokenHelper::getTokenBaseFromString(*currentWord) == Token::Shape) {
      tree->childrenList.push_back(parseShape());
    }
  }
  expectToken(Token::CloseCurlyBracket);

  return tree;
}

RST* Parser::parseShape() {
  ShapeRST* tree = new ShapeRST;

  tree->type = *currentWord;
  nextWord();
  expectIdentifier();
  tree->identifier = *currentWord;
  tree->childrenList.push_back(parseStructure());

  return tree;
}

RST* Parser::parseCamera() {
  CameraRST* tree = new CameraRST;

  tree->type = *currentWord;
  nextWord();
  expectIdentifier();
  tree->identifier = *currentWord;
  tree->childrenList.push_back(parseStructure());

  return tree;
}

RST* Parser::parseStructure() {
  StructureRST* tree = new StructureRST;

  nextWord();
  expectToken(Token::OpenCurlyBracket);
  nextWord();

  while (TokenHelper::getTokenTypeFromString(*currentWord) == TokenType::Function) {
    tree->childrenList.push_back(parseFunction());
  }

  while (TokenHelper::getTokenTypeFromString(*currentWord) == TokenType::Identifier) {
    tree->childrenList.push_back(parseProperty());
  }

  expectToken(Token::CloseCurlyBracket);
  nextWord();

  return tree;
}

RST* Parser::parseFunction() {
  FunctionRST* tree = new FunctionRST;

  nextWord();
  tree->identifier = *currentWord;
  nextWord();
  expectToken(Token::OpenParentheses);
  nextWord();

  while (TokenHelper::getTokenTypeFromString(*currentWord) == TokenType::Identifier) {
    tree->childrenList.push_back(parseProperty());
  }

  expectToken(Token::CloseParentheses);
  nextWord();

  return tree;
}

RST* Parser::parseProperty() {
  PropertyRST* tree = new PropertyRST;

  std::string identifier = *currentWord;
  tree->identifier = *currentWord;

  nextWord();
  expectToken(Token::Equals);
  nextWord();

  if (TokenHelper::getTokenTypeFromString(*currentWord) == TokenType::Constant) {
    tree->dataList.push_back(*currentWord);
    nextWord();
  }
  else {
    expectToken(Token::OpenSquareBracket);
    nextWord();

    while (TokenHelper::getTokenTypeFromString(*currentWord) == TokenType::Constant) {
      tree->dataList.push_back(*currentWord);
      nextWord();
    }

    expectToken(Token::CloseSquareBracket);
    nextWord();
  }

  return tree;
}