#include "parser_memory.h"

ParserMemory::ParserMemory() {

}

ParserMemory::~ParserMemory() {

}

void ParserMemory::pushTransformationMatrix(TransformationMatrix* transformationMatrix) {
  transformationMatrixList.push_back(transformationMatrix);
}

void ParserMemory::pushShape(Shape* shape, std::string identifier) {
  shapeList.push_back(shape);
  stringShapeMap.insert(std::pair<std::string, Shape*>(identifier, shape));
}

void ParserMemory::mapLastShapeTransformationMatrix() {
  Shape* lastShape = shapeList[shapeList.size() - 1];
  TransformationMatrix* lastTransformationMatrix = transformationMatrixList[transformationMatrixList.size() -1];
  shapeTransformationMatrixMap.insert(std::pair<Shape*, TransformationMatrix*>(lastShape, lastTransformationMatrix));
}

void ParserMemory::linkAllShapeTransformationMatrix() {
  std::map<Shape*, TransformationMatrix*>::iterator mapIterator;

  for (mapIterator = shapeTransformationMatrixMap.begin(); mapIterator != shapeTransformationMatrixMap.end(); mapIterator++) {
    Shape* shape = mapIterator->first;
    TransformationMatrix* transformationMatrix = mapIterator->second;

    shape->setTransformationMatrix(transformationMatrix, new TransformationMatrix(transformationMatrix->getInverseMatrix()));
  }
}

TransformationMatrix* ParserMemory::getLastTransformationMatrix() {
  return transformationMatrixList[transformationMatrixList.size() - 1];
}

Shape* ParserMemory::getLastShape() {
  return shapeList[shapeList.size() - 1];
}