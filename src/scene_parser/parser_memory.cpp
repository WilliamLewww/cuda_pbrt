#include "parser_memory.h"

ParserMemory::ParserMemory() {
  functionParserStack = new ParserStack<FunctionType>(&ParserStackMaps::stringFunctionTypeMap, &ParserStackMaps::functionTypePropertyCountMap);
  functionParserStack->setCurrentTypeFromString("none");

  constructorParserStack = new ParserStack<ConstructorType>(&ParserStackMaps::stringConstructorTypeMap, &ParserStackMaps::constructorTypePropertyCountMap);
  constructorParserStack->setCurrentTypeFromString("none");
}

ParserMemory::~ParserMemory() {
  delete functionParserStack;
  delete constructorParserStack;
}

void ParserMemory::setCurrentFunctionTypeFromString(std::string word) {
  functionParserStack->setCurrentTypeFromString(word);
}

FunctionType ParserMemory::getCurrentFunctionType() {
  return functionParserStack->getCurrentType();
}

bool ParserMemory::checkPropertyFunctionStackFull() {
  return functionParserStack->checkPropertyStackFull();
}

bool ParserMemory::checkPropertyFunctionStackEmpty() {
  return functionParserStack->checkPropertyStackEmpty();
}

void ParserMemory::pushPropertyFunction(Property property) {
  functionParserStack->pushProperty(property);
}

void ParserMemory::popPropertyFunction() {
  functionParserStack->popProperty();
}

Property ParserMemory::getPropertyFunctionStackTop() {
  return functionParserStack->getPropertyStackTop();
}

void ParserMemory::setCurrentConstructorTypeFromString(std::string word) {
  constructorParserStack->setCurrentTypeFromString(word);
}

ConstructorType ParserMemory::getCurrentConstructorType() {
  return constructorParserStack->getCurrentType();
}

bool ParserMemory::checkPropertyConstructorStackFull() {
  return constructorParserStack->checkPropertyStackFull();
}

bool ParserMemory::checkPropertyConstructorStackEmpty() {
  return constructorParserStack->checkPropertyStackEmpty();
}

void ParserMemory::pushPropertyConstructor(Property property) {
  constructorParserStack->pushProperty(property);
}

void ParserMemory::popPropertyConstructor() {
  constructorParserStack->popProperty();
}

Property ParserMemory::getPropertyConstructorStackTop() {
  return constructorParserStack->getPropertyStackTop();
}

void ParserMemory::pushShape(Shape* shape, std::string identifier) {
  shapeList.push_back(shape);
  stringShapeMap.insert(std::pair<std::string, Shape*>(identifier, shape));
}

void ParserMemory::pushCamera(Camera* camera, std::string identifier) {
  cameraList.push_back(camera);
  stringCameraMap.insert(std::pair<std::string, Camera*>(identifier, camera));
}

void ParserMemory::pushTransformationMatrix(TransformationMatrix* transformationMatrix) {
  transformationMatrixList.push_back(transformationMatrix);
}

void ParserMemory::mapLastShapeTransformationMatrix() {
  Shape* lastShape = shapeList[shapeList.size() - 1];
  TransformationMatrix* lastTransformationMatrix = transformationMatrixList[transformationMatrixList.size() -1];
  shapeTransformationMatrixMap.insert(std::pair<Shape*, TransformationMatrix*>(lastShape, lastTransformationMatrix));
}

void ParserMemory::mapLastCameraTransformationMatrix() {
  Camera* lastCamera = cameraList[cameraList.size() - 1];
  TransformationMatrix* lastTransformationMatrix = transformationMatrixList[transformationMatrixList.size() -1];
  cameraTransformationMatrixMap.insert(std::pair<Camera*, TransformationMatrix*>(lastCamera, lastTransformationMatrix));
}

void ParserMemory::linkAllShapeTransformationMatrix() {
  std::map<Shape*, TransformationMatrix*>::iterator mapIterator;

  for (mapIterator = shapeTransformationMatrixMap.begin(); mapIterator != shapeTransformationMatrixMap.end(); mapIterator++) {
    Shape* shape = mapIterator->first;
    TransformationMatrix* transformationMatrix = mapIterator->second;

    shape->setTransformationMatrix(transformationMatrix, new TransformationMatrix(transformationMatrix->getInverseMatrix()));
  }
}

void ParserMemory::linkAllCameraTransformationMatrix() {
  std::map<Camera*, TransformationMatrix*>::iterator mapIterator;

  for (mapIterator = cameraTransformationMatrixMap.begin(); mapIterator != cameraTransformationMatrixMap.end(); mapIterator++) {
    Camera* camera = mapIterator->first;
    TransformationMatrix* transformationMatrix = mapIterator->second;

    camera->setTransformationMatrix(transformationMatrix);
  }
}

Shape* ParserMemory::getLastShape() {
  return shapeList[shapeList.size() - 1];
}

Camera* ParserMemory::getLastCamera() {
  return cameraList[cameraList.size() - 1];
}

TransformationMatrix* ParserMemory::getLastTransformationMatrix() {
  return transformationMatrixList[transformationMatrixList.size() - 1];
}

Scene* ParserMemory::createScene() {
  Scene* scene = new Scene();

  return scene;
}