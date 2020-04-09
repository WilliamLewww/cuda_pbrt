#pragma once
#include <vector>
#include <stack>
#include <map>

#include "../shape.h"
#include "../camera.h"
#include "../transformation_matrix.h"
#include "../scene.h"

enum class FunctionType {
  None, Translate, Scale, LookAt
};

enum class ConstructorType {
  None, Sphere
};

struct Property {
  std::string identifier;
  std::vector<std::string> dataList;
};

class ParserMemory {
private:
  static std::map<std::string, FunctionType> stringFunctionTypeMap;
  static std::map<std::string, ConstructorType> stringConstructorTypeMap;
  static std::map<FunctionType, int> functionTypePropertyCountRequirementMap;
  static std::map<ConstructorType, int> shapeTypeConstructorCountRequirementMap;

  FunctionType currentFunctionType;
  std::stack<Property> propertyFunctionStack;

  ConstructorType currentConstructorType;
  std::stack<Property> propertyConstructorStack;

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