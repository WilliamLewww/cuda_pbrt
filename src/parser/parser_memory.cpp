#include "parser_memory.h"

std::map<std::string, Function> ParserMemory::stringFunctionMap = {
  {"none", Function::None}, {"translate", Function::Translate}, {"scale", Function::Scale}, {"lookAt", Function::LookAt}
};

std::map<Function, int> ParserMemory::functionPropertyCountRequirementMap = {
  {Function::None, 0}, {Function::Translate, 1}, {Function::Scale, 1}, {Function::LookAt, 3}
};

ParserMemory::ParserMemory() {
  currentFunction = Function::None;
}

ParserMemory::~ParserMemory() {

}

void ParserMemory::setCurrentFunctionFromString(std::string word) {
  currentFunction = stringFunctionMap[word];
}

Function ParserMemory::getCurrentFunction() {
  return currentFunction;
}

bool ParserMemory::checkPropertyStackFull() {
  return propertyStack.size() >= functionPropertyCountRequirementMap[currentFunction];
}

bool ParserMemory::checkPropertyStackEmpty() {
  return propertyStack.empty();
}

void ParserMemory::pushProperty(Property property) {
  propertyStack.push(property);
}

void ParserMemory::popProperty() {
  propertyStack.pop();
}

Property ParserMemory::getPropertyStackTop() {
  return propertyStack.top();
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

  for (int x = 0; x < shapeList.size(); x++) {
    scene->addShape(shapeList[x]);
  }

  return scene;
}