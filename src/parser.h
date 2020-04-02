#pragma once
#include <fstream>
#include <string>
#include <map>
#include "scene.h"

enum class TokenType {
  Type, Terminal, Identifier, Constant
};

enum class Token {
  World, Camera, Sphere, Radius, Translate, Rotate, Scale, Equals, OpenCurlyBracket, CloseCurlyBracket, OpenSquareBracket, CloseSquareBracket
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
  std::string* currentWord;

  bool nextToken();
  TokenType checkTokenType();

  void expectToken(Token token);
  void expectIdentifier();

  void printTree(RST* root, int offset);

  RST* parseWorld();
  RST* parseBlock();
  RST* parseShape();
  RST* parseStructure();
  RST* parseProperty();

  static std::map<std::string, Token> stringTokenMap;
  static std::map<Token, TokenType> tokenTypeMap;
public:
  Parser();
  ~Parser();

  Scene* createSceneFromFile(const char* filename);
};