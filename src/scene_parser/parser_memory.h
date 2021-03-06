#pragma once
#include <vector>
#include <stack>
#include <map>

#include "parser_stack.h"

#include "../shape.h"
#include "../camera.h"
#include "../transformation_matrix.h"
#include "../scene.h"
#include "../bvh.h"

class ParserMemory {
private:
  ParserStack<FunctionType>* functionParserStack;
  ParserStack<ConstructorType>* constructorParserStack;

  std::map<std::string, Shape*> stringShapeMap;
  std::map<std::string, Camera*> stringCameraMap;

  std::map<Shape*, TransformationMatrix*> shapeTransformationMatrixMap;
  std::map<Camera*, TransformationMatrix*> cameraTransformationMatrixMap;

  std::vector<Shape*> shapeList;
  std::vector<Camera*> cameraList;

  std::vector<TransformationMatrix*> transformationMatrixList;
public:
  ParserMemory();
  ~ParserMemory();

  void setCurrentFunctionTypeFromString(std::string word);
  FunctionType getCurrentFunctionType();
  bool checkPropertyFunctionStackFull();
  bool checkPropertyFunctionStackEmpty();

  void pushPropertyFunction(Property property);
  void popPropertyFunction();
  Property getPropertyFunctionStackTop();

  void setCurrentConstructorTypeFromString(std::string word);
  ConstructorType getCurrentConstructorType();
  bool checkPropertyConstructorStackFull();
  bool checkPropertyConstructorStackEmpty();

  void pushPropertyConstructor(Property property);
  void popPropertyConstructor();
  Property getPropertyConstructorStackTop();

  void pushShape(Shape* shape, std::string identifier);
  void pushCamera(Camera* camera, std::string identifier);
  
  void pushTransformationMatrix(TransformationMatrix* transformationMatrix);
  void mapLastShapeTransformationMatrix();
  void mapLastCameraTransformationMatrix();

  void linkAllShapeTransformationMatrix();
  void linkAllCameraTransformationMatrix();

  Shape* getLastShape();
  Camera* getLastCamera();
  TransformationMatrix* getLastTransformationMatrix();

  Scene* createScene();
};