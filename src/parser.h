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