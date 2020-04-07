#pragma once
#include <vector>
#include <string>

struct RST {
  std::vector<RST*> childrenList;

  virtual std::string toString();
  virtual std::string getTypeString();
};

struct ShapeRST : RST {
  std::string type;
  std::string identifier;

  std::string toString() override;
  std::string getTypeString() override;
};

struct CameraRST : RST {
  std::string type;
  std::string identifier;

  std::string toString() override;
  std::string getTypeString() override;
};

struct FunctionRST : RST {
  std::string identifier;

  std::string toString() override;
  std::string getTypeString() override;
};

struct PropertyRST : RST {
  std::string identifier;
  std::vector<std::string> dataList;

  std::string toString() override;
  std::string getTypeString() override;
};

struct StructureRST : RST {
  std::string toString() override;
  std::string getTypeString() override;
};

struct WorldRST : RST {
  std::string toString() override;
  std::string getTypeString() override;
};