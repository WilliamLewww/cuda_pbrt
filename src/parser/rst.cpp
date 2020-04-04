#include "rst.h"

std::string RST::getTypeString() { return "RST"; }
std::string ShapeRST::getTypeString() { return "ShapeRST"; }
std::string PropertyRST::getTypeString() { return "PropertyRST"; }
std::string StructureRST::getTypeString() { return "StructureRST"; }
std::string WorldRST::getTypeString() { return "WorldRST"; }
std::string BlockRST::getTypeString() { return "BlockRST"; }

std::string RST::toString() {
  std::string printOut = "RST";
  return printOut;
}

std::string ShapeRST::toString() {
  std::string printOut = "ShapeRST: ";
  printOut += type + " -> " + identifier;
  return printOut;
}

std::string PropertyRST::toString() {
  std::string printOut = "PropertyRST: ";
  printOut += identifier + " -> [";
  for (int x = 0; x < dataList.size(); x++) {
    printOut += dataList[x];
    if (x == dataList.size() - 1) {
      printOut += "]";
    }
    else {
      printOut += ", ";
    }
  }

  return printOut;
}

std::string StructureRST::toString() {
  std::string printOut = "StructureRST";
  return printOut;
}

std::string WorldRST::toString() {
  std::string printOut = "WorldRST";
  return printOut;
}

std::string BlockRST::toString() {
  std::string printOut = "BlockRST";
  return printOut;
}