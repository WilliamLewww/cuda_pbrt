#include "token.h"

std::map<std::string, Token> TokenGenerator::stringTokenMap = {
  {"World", Token::World}, {"Camera", Token::Camera}, {"Sphere", Token::Sphere}, {"Radius", Token::Radius}, {"Translate", Token::Translate},
  {"Rotate", Token::Rotate}, {"Scale", Token::Scale}, {"=", Token::Equals}, {"{", Token::OpenCurlyBracket}, {"}", Token::CloseCurlyBracket}, 
  {"[", Token::OpenSquareBracket}, {"]", Token::CloseSquareBracket}
};

std::map<Token, TokenType> TokenGenerator::tokenTypeMap = {
  {Token::World, TokenType::Type}, {Token::Camera, TokenType::Type}, {Token::Sphere, TokenType::Type}, {Token::Radius, TokenType::Type},
  {Token::Translate, TokenType::Type}, {Token::Rotate, TokenType::Type}, {Token::Scale, TokenType::Type}, {Token::Equals, TokenType::Terminal}, 
  {Token::OpenCurlyBracket, TokenType::Terminal}, {Token::CloseCurlyBracket, TokenType::Terminal}, {Token::OpenSquareBracket, TokenType::Terminal}, 
  {Token::CloseSquareBracket, TokenType::Terminal}
};

TokenType TokenGenerator::getTokenFromWord(std::string word) {
  if (stringTokenMap.find(word) != stringTokenMap.end()) {
    return tokenTypeMap[stringTokenMap[word]];
  }
  else {
    for (int x = 0; x < word.length(); x++) {
      if (std::isalpha(word[x])) {
        return TokenType::Identifier;
      }
    }
  }

  return TokenType::Constant;
}