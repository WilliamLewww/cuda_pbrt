#include "token.h"

std::map<std::string, Token> TokenHelper::stringTokenMap = {
  {"World", Token::World}, {"Camera", Token::Camera}, {"Sphere", Token::Sphere}, {"=", Token::Equals}, {"{", Token::OpenCurlyBracket}, {"}", Token::CloseCurlyBracket}, 
  {"[", Token::OpenSquareBracket}, {"]", Token::CloseSquareBracket}, {"Shape", Token::Shape}, {"OrthographicCamera", Token::OrthographicCamera},
  {"Function", Token::Function}, {"(", Token::OpenParentheses}, {")", Token::CloseParentheses},
};

std::map<Token, TokenType> TokenHelper::tokenTypeMap = {
  {Token::World, TokenType::Type}, {Token::Camera, TokenType::Type}, {Token::Sphere, TokenType::Type}, {Token::Equals, TokenType::Terminal}, 
  {Token::OpenCurlyBracket, TokenType::Terminal}, {Token::CloseCurlyBracket, TokenType::Terminal}, {Token::OpenSquareBracket, TokenType::Terminal}, 
  {Token::CloseSquareBracket, TokenType::Terminal}, {Token::Shape, TokenType::Type}, {Token::OrthographicCamera, TokenType::Type},
  {Token::Function, TokenType::Function}, {Token::OpenParentheses, TokenType::Terminal}, {Token::CloseParentheses, TokenType::Terminal}
};

std::map<Token, Token> TokenHelper::tokenBaseMap = {
  {Token::Shape, Token::Shape}, {Token::Sphere, Token::Shape}, {Token::Camera, Token::Camera}, {Token::OrthographicCamera, Token::Camera}
};

Token TokenHelper::getTokenBaseFromString(std::string word) {
  return tokenBaseMap[stringTokenMap[word]];
}

Token TokenHelper::getTokenFromString(std::string word) {
  return stringTokenMap[word];
}

TokenType TokenHelper::getTokenTypeFromString(std::string word) {
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