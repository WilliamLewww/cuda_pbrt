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
};

struct ShapeRST : RST {
  std::string* type;
  std::string* identifier;
};

struct StructureRST : RST {
  std::map<std::string, std::vector<std::string>*> dataMap;
};

struct WorldRST : RST {};
struct BlockRST : RST {};

class Parser {
private:
  std::fstream* file;
  std::string* currentToken;

  bool nextToken();
  TokenType checkTokenType();

  void expectToken(std::string token);
  void expectIdentifier();

  RST* ParseWorld();
  RST* ParseBlock();
  RST* ParseShape();
  RST* ParseStructure();
public:
  Parser();
  ~Parser();

  Scene* createSceneFromFile(const char* filename);
};