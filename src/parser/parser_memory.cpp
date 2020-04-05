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

void ParserMemory::connectLastShapeTransformationMatrix() {
  TransformationMatrix* transformationMatrix = transformationMatrixList[transformationMatrixList.size() - 1];
  shapeList[shapeList.size() - 1]->setTransformationMatrix(transformationMatrix, new TransformationMatrix(transformationMatrix->getInverseMatrix()));
}