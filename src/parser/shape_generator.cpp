#include "shape_generator.h"

std::map<std::string, Shape*> ShapeGenerator::stringShapeMap = {
  {"Sphere", new Sphere(currentTransformationMatrix, new TransformationMatrix(currentTransformationMatrix->getInverseMatrix()))}
};

TransformationMatrix* ShapeGenerator::currentTransformationMatrix = nullptr;

Shape* ShapeGenerator::generateShapeFromString(std::string word) {
  return stringShapeMap[word];
}

void ShapeGenerator::setCurrentTransformationMatrix(TransformationMatrix* transformationMatrix) {
  currentTransformationMatrix = transformationMatrix;
}