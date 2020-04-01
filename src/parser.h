#pragma once
#include <fstream>
#include <string>
#include <map>
#include "scene.h"

enum class TokenType {
  Type, Identifier, Constant, Terminal
};

struct RST {
  std::vector<RST*> childrenList;

  virtual std::string getName() { return "RST"; }
};

struct ShapeRST : RST {
  std::string* type;
  std::string* identifier;

  std::string getName() override { return "ShapeRST"; }
};

struct PropertyRST : RST {
  std::map<std::string, std::vector<std::string>*> dataMap;

  std::string getName() override { return "PropertyRST"; }
};

struct StructureRST : RST {
  std::string getName() override { return "StructureRST"; }
};

struct WorldRST : RST {
  std::string getName() override { return "WorldRST"; }
};

struct BlockRST : RST {
  std::string getName() override { return "BlockRST"; }
};

class Parser {
private:
  std::fstream* file;
  std::string* currentToken;

  bool nextToken();
  TokenType checkTokenType();

  void expectToken(std::string token);
  void expectIdentifier();

  void printTree(RST* root, int offset);

  RST* parseWorld();
  RST* parseBlock();
  RST* parseShape();
  RST* parseStructure();
  RST* parseProperty();
public:
  Parser();
  ~Parser();

  Scene* createSceneFromFile(const char* filename);
};