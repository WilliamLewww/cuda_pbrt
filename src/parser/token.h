#pragma once
#include <map>
#include <string>

enum class TokenType {
  Type, Terminal, Identifier, Constant
};

enum class Token {
  World, Camera, Sphere, Radius, Translate, Rotate, Scale, Equals, OpenCurlyBracket, CloseCurlyBracket, OpenSquareBracket, CloseSquareBracket,
  Shape
};

class TokenHelper {
public:
  static std::map<std::string, Token> stringTokenMap;
  static std::map<Token, TokenType> tokenTypeMap;
  static std::map<Token, Token> tokenBaseMap;

  static Token getTokenBaseFromString(std::string word);
  static Token getTokenFromString(std::string word);
  static TokenType getTokenTypeFromString(std::string word);
};