#include "parser_stack.h"

template <typename Type>
ParserStack<Type>::ParserStack(std::map<std::string, Type>* stringTypeMap, std::map<Type, int>* typePropertyCountRequirementMap) {
  this->stringTypeMap = stringTypeMap;
  this->typePropertyCountRequirementMap = typePropertyCountRequirementMap;
}

template <typename Type>
ParserStack<Type>::~ParserStack() {

}

template <typename Type>
void ParserStack<Type>::setCurrentTypeFromString(std::string word) {
  currentType = (*stringTypeMap)[word];
}

template <typename Type>
Type ParserStack<Type>::getCurrentType() {
  return currentType;
}

template <typename Type>
bool ParserStack<Type>::checkPropertyStackFull() {
  return propertyStack.size() >= (*typePropertyCountRequirementMap)[currentType];
}

template <typename Type>
bool ParserStack<Type>::checkPropertyStackEmpty() {
  return propertyStack.empty();
}

template <typename Type>
void ParserStack<Type>::pushProperty(Property property) {
  propertyStack.push(property);
}

template <typename Type>
void ParserStack<Type>::popProperty() {
  propertyStack.pop();
}

template <typename Type>
Property ParserStack<Type>::getPropertyStackTop() {
  return propertyStack.top();
}