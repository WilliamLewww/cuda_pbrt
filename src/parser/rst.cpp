#include "rst.h"

std::string RST::getTypeString() { return "RST"; }
std::string ShapeRST::getTypeString() { return "ShapeRST"; }
std::string FunctionRST::getTypeString() { return "FunctionRST"; }
std::string PropertyRST::getTypeString() { return "PropertyRST"; }
std::string StructureRST::getTypeString() { return "StructureRST"; }
std::string CameraRST::getTypeString() { return "CameraRST"; }
std::string WorldRST::getTypeString() { return "WorldRST"; }

std::string RST::toString() {
  std::string printOut = "RST";
  return printOut;
}

std::string ShapeRST::toString() {
  std::string printOut = "Shape: ";
  printOut += type + " -> " + identifier;
  return printOut;
}

std::string CameraRST::toString() {
  std::string printOut = "Camera: ";
  printOut += type + " -> " + identifier;
  return printOut;
}

std::string FunctionRST::toString() {
  std::string printOut = "Function: ";
  printOut += identifier;
  return printOut;
}

std::string PropertyRST::toString() {
  std::string printOut = "Property: ";
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
  std::string printOut = "Structure";
  return printOut;
}

std::string WorldRST::toString() {
  std::string printOut = "World";
  return printOut;
}