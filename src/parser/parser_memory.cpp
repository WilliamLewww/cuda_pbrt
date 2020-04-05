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
  shapeMap.insert(std::pair<std::string, Shape*>(identifier, shape));
}

TransformationMatrix* ParserMemory::getLastTransformationMatrix() {
  return transformationMatrixList[transformationMatrixList.size() - 1];
}

Shape* ParserMemory::getLastShape() {
  return shapeList[shapeList.size() - 1];
}