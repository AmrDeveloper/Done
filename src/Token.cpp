#include "../include/Token.h"

Token::Token(TokenType type, const std::string &aLexeme,
             const std::string &aLiteral, int aLine, int aStart, int aEnd) {
  tokenType = type;
  lexeme = aLexeme;
  literal = aLiteral;
  line = aLine;
  start = aStart;
  end = aEnd;
}

Token::Token(TokenType type, const std::string &aLexeme,
             const std::string &aLiteral, int aLine) {
  tokenType = type;
  tokenType = type;
  lexeme = aLexeme;
  literal = aLiteral;
  line = aLine;
  start = -1;
  end = -1;
}
