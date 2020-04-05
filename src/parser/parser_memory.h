#pragma once
#include <vector>
#include <stack>
#include <map>

#include "../shape.h"

class ParserMemory {
private:
  std::vector<Shape*> shapeList;
  std::map<std::string, Shape*> shapeMap;
public:
  ParserMemory();
  ~ParserMemory();

  void pushShape(Shape* shape, std::string identifier);
};