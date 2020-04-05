#pragma once
#include <vector>
#include <stack>
#include <map>

#include "../shape.h"
#include "../transformation_matrix.h"

class ParserMemory {
private:
  std::map<std::string, Shape*> stringShapeMap;
  std::map<Shape*, TransformationMatrix*> shapeTransformationMatrixMap;

  std::vector<Shape*> shapeList;
  std::vector<TransformationMatrix*> transformationMatrixList;
public:
  ParserMemory();
  ~ParserMemory();

  void pushTransformationMatrix(TransformationMatrix* transformationMatrix);
  void pushShape(Shape* shape, std::string identifier);
  void mapLastShapeTransformationMatrix();

  void linkAllShapeTransformationMatrix();
};