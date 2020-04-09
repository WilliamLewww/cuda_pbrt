#pragma once
#include <map>
#include <stack>
#include <string>
#include <vector>

enum class StackType {
  Function
};

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

template <class Type>
class ParserStack {
private:
  std::map<std::string, Type>* stringTypeMap;
  std::map<Type, int>* typePropertyCountMap;

  Type currentType;
  std::stack<Property> propertyStack;
public:
  ParserStack(std::map<std::string, Type>* stringTypeMap, std::map<Type, int>* typePropertyCountMap);
  ~ParserStack();

  void setCurrentTypeFromString(std::string word);
  Type getCurrentType();

  bool checkPropertyStackFull();
  bool checkPropertyStackEmpty();

  void pushProperty(Property property);
  void popProperty();
  Property getPropertyStackTop();
};

struct ParserStackMaps {
  static std::map<std::string, FunctionType> stringFunctionTypeMap;
  static std::map<std::string, ConstructorType> stringConstructorTypeMap;

  static std::map<FunctionType, int> functionTypePropertyCountMap;
  static std::map<ConstructorType, int> constructorTypePropertyCountMap;
};