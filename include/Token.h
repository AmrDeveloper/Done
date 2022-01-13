#ifndef DONELANG_TOKEN_H
#define DONELANG_TOKEN_H

#include "TokenType.h"
#include <string>

class Token {
public:
  Token(TokenType type, const std::string &aLexeme, const std::string &aLiteral,
        int aLine, int start, int end);

  Token(TokenType type, const std::string &aLexeme, const std::string &aLiteral,
        int aLine);

  TokenType tokenType;
  std::string lexeme;
  std::string literal;
  int line;
  int start;
  int end;
};
#endif
