#pragma once
#include <map>
#include <string>

enum class TokenType {
  Type, Terminal, Identifier, Constant, Function
};

enum class Token {
  World, Camera, Sphere, Radius, Translate, Rotate, Scale, Equals, OpenCurlyBracket, CloseCurlyBracket, OpenSquareBracket, CloseSquareBracket,
  Shape, SimpleCamera, Function, OpenParentheses, CloseParentheses, Position, Target, Up
};

class TokenHelper {
private:
  static std::map<std::string, Token> stringTokenMap;
  static std::map<Token, TokenType> tokenTypeMap;
  static std::map<Token, Token> tokenBaseMap;
public:
  static Token getTokenBaseFromString(std::string word);
  static Token getTokenFromString(std::string word);
  static TokenType getTokenTypeFromString(std::string word);
};