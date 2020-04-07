#pragma once
#include <vector>
#include <stack>
#include <map>

#include "../shape.h"
#include "../camera.h"
#include "../transformation_matrix.h"
#include "../scene.h"

class ParserMemory {
private:
  std::map<std::string, Shape*> stringShapeMap;
  std::map<std::string, Camera*> stringCameraMap;

  std::map<Shape*, TransformationMatrix*> shapeTransformationMatrixMap;

  std::vector<Shape*> shapeList;
  std::vector<Camera*> cameraList;

  std::vector<TransformationMatrix*> transformationMatrixList;
public:
  ParserMemory();
  ~ParserMemory();

  void pushShape(Shape* shape, std::string identifier);
  void pushCamera(Camera* camera, std::string identifier);
  
  void pushTransformationMatrix(TransformationMatrix* transformationMatrix);
  void mapLastShapeTransformationMatrix();

  void linkAllShapeTransformationMatrix();

  Shape* getLastShape();
  TransformationMatrix* getLastTransformationMatrix();

  Scene* createScene();
};