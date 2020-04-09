#pragma once
#include <map>
#include <stack>
#include <string>
#include <vector>

enum class FunctionType {
  None, Translate, Scale, LookAt
};

struct Property {
  std::string identifier;
  std::vector<std::string> dataList;
};

template <class Type>
class ParserStack {
private:
  std::map<std::string, Type>* stringTypeMap;
  std::map<Type, int>* typePropertyCountRequirementMap;

  Type currentType;
  std::stack<Property> propertyStack;
public:
  ParserStack(std::map<std::string, Type>* stringTypeMap, std::map<Type, int>* typePropertyCountRequirementMap);
  ~ParserStack();

  void setCurrentTypeFromString(std::string word);
  Type getCurrentType();

  bool checkPropertyStackFull();
  bool checkPropertyStackEmpty();

  void pushProperty(Property property);
  void popProperty();
  Property getPropertyStackTop();
};

class ParserStackHelper {
private:
  static std::map<std::string, FunctionType> stringFunctionTypeMap;
  static std::map<FunctionType, int> functionTypePropertyCountRequirementMap;
public:
};