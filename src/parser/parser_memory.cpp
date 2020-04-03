#include "parser_memory.h"

ParserMemory::ParserMemory() {

}

ParserMemory::~ParserMemory() {
  for (int x = 0; x < shapeList.size(); x++) {
    delete shapeList[x];
  }

  shapeList.clear();
}