#pragma once
#include <vector>
#include <stack>
#include <map>

#include "../shape.h"

class ParserMemory {
private:
  std::vector<Shape*> shapeList;
public:
  ParserMemory();
  ~ParserMemory();
};