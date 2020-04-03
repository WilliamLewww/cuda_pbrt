#pragma once
#include <vector>
#include <string>

struct RST {
  std::vector<RST*> childrenList;

  virtual std::string toString();
};

struct ShapeRST : RST {
  std::string type;
  std::string identifier;

  std::string toString() override;
};

struct PropertyRST : RST {
  std::string identifier;
  std::vector<std::string> dataList;

  std::string toString() override;
};

struct StructureRST : RST {
  std::string toString() override;
};

struct WorldRST : RST {
  std::string toString() override;
};

struct BlockRST : RST {
  std::string toString() override;
};