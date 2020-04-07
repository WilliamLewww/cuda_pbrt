#pragma once
#include <vector>
#include <stack>
#include <map>

#include "../shape.h"
#include "../camera.h"
#include "../transformation_matrix.h"
#include "../scene.h"

enum Function {
  None, Translate, Scale, LookAt
};

struct Property {
  std::string identifier;
  std::vector<std::string> dataList;
};

class ParserMemory {
private:
  static std::map<std::string, Function> stringFunctionMap;
  static std::map<Function, int> functionPropertyCountRequirementMap;

  Function currentFunction;
  std::stack<Property> propertyStack;

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

  void setCurrentFunctionFromString(std::string word);
  Function getCurrentFunction();
  bool checkPropertyStackFull();
  bool checkPropertyStackEmpty();

  void pushProperty(Property property);
  void popProperty();
  Property getPropertyStackTop();

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