#include "parser_memory.h"

ParserMemory::ParserMemory() {

}

ParserMemory::~ParserMemory() {
  for (int x = 0; x < shapeList.size(); x++) {
    delete shapeList[x];
  }

  shapeList.clear();
}

void ParserMemory::pushShape(Shape* shape, std::string identifier) {
  shapeList.push_back(shape);
  shapeMap.insert(std::pair<std::string, Shape*>(identifier, shape));
}