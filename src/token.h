#pragma once
#include <map>
#include <string>

enum class TokenType {
  Type, Terminal, Identifier, Constant
};

enum class Token {
  World, Camera, Sphere, Radius, Translate, Rotate, Scale, Equals, OpenCurlyBracket, CloseCurlyBracket, OpenSquareBracket, CloseSquareBracket
};

class TokenGenerator {
public:
  static std::map<std::string, Token> stringTokenMap;
  static std::map<Token, TokenType> tokenTypeMap;

  static TokenType getTokenFromWord(std::string word);
};