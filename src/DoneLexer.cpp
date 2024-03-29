#include "../include/DoneLexer.h"

#include <algorithm>
#include <iostream>

DoneLexer::DoneLexer(const std::string &aSource, ErrorHandler &aErrorHandler)
    : errorHandler(aErrorHandler) {
  line = 1;
  start = 0;
  current = 0;
  source = aSource;

  reservedKeywords["import"] = TokenType::IMPORT;
  reservedKeywords["include"] = TokenType::INCLUDE;

  reservedKeywords["if"] = TokenType::IF;
  reservedKeywords["elif"] = TokenType::ELSE_IF;
  reservedKeywords["else"] = TokenType::ELSE;

  reservedKeywords["for"] = TokenType::FOR;
  reservedKeywords["do"] = TokenType::DO;
  reservedKeywords["while"] = TokenType::WHILE;
  reservedKeywords["continue"] = TokenType::CONTINUE;
  reservedKeywords["break"] = TokenType::BREAK;

  reservedKeywords["fun"] = TokenType::FUN;
  reservedKeywords["var"] = TokenType::VAR;
  reservedKeywords["const"] = TokenType::CONST;
  reservedKeywords["return"] = TokenType::RETURN;

  reservedKeywords["null"] = TokenType::NIL;
  reservedKeywords["true"] = TokenType::TRUE;
  reservedKeywords["false"] = TokenType::FALSE;

  reservedKeywords["or"] = TokenType::OR;
  reservedKeywords["and"] = TokenType::AND;
  reservedKeywords["xor"] = TokenType::XOR;

  reservedKeywords["enum"] = TokenType::ENUM;
  reservedKeywords["struct"] = TokenType::STRUCT;

  reservedKeywords["new"] = TokenType::NEW;
  reservedKeywords["free"] = TokenType::FREE;
}

std::vector<Token> DoneLexer::scanSourceCode() {
  while (!isAtEnd()) {
    start = current;
    scanAndAddToken();
  }
  tokens.emplace_back(TokenType::END_OF_FILE, "", "", line);
  return tokens;
}

char DoneLexer::advanceAndGetChar() {
  ++current;
  return source[current - 1];
}

void DoneLexer::scanAndAddToken() {
  const char c = advanceAndGetChar();
  switch (c) {
  case '(':
    addToken(TokenType::LEFT_PAREN);
    break;
  case ')':
    addToken(TokenType::RIGHT_PAREN);
    break;
  case '{':
    addToken(TokenType::LEFT_BRACE);
    break;
  case '}':
    addToken(TokenType::RIGHT_BRACE);
    break;
  case '[':
    addToken(TokenType::ARRAY_LEFT_BRACKET);
    break;
  case ']':
    addToken(TokenType::ARRAY_RIGHT_BRACKET);
    break;
  case ',':
    addToken(TokenType::COMMA);
    break;
  case ':':
    addToken(matchAndAdvance('=')   ? TokenType::COLON_EQUAL
             : matchAndAdvance(':') ? TokenType::COLON_COLON
                                    : COLON);
    break;
  case '.':
    addToken(TokenType::DOT);
    break;
  case '-':
    addToken(matchAndAdvance('-')   ? TokenType::MINUS_MINUS
             : matchAndAdvance('>') ? LAMBDA
                                    : TokenType::MINUS);
    break;
  case '+':
    addToken(matchAndAdvance('+') ? TokenType::PLUS_PLUS : TokenType::PLUS);
    break;
  case ';':
    addToken(TokenType::SEMICOLON);
    break;
  case '*':
    addToken(matchAndAdvance('*') ? TokenType::STAR_STAR : TokenType::STAR);
    break;
  case '&':
    addToken(TokenType::ADDRESS);
    break;
  case '%':
    addToken(TokenType::PERCENT);
    break;
  case '?':
    addToken(matchAndAdvance(':') ? TokenType::ELVIS : TokenType::TERNARY);
    break;
  case '=':
    addToken(matchAndAdvance('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
    break;
  case '<':
    addToken(matchAndAdvance('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
    break;
  case '>':
    addToken(matchAndAdvance('=') ? TokenType::GREATER_EQUAL
                                  : TokenType::GREATER);
    break;
  case '!':
    addToken(matchAndAdvance('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
    break;
  case '/':
    if (matchAndAdvance('/')) {
      while (getCurrentChar() != '\n' && !isAtEnd())
        advanceAndGetChar();
    } else {
      addToken(TokenType::SLASH);
    }
    break;
  case ' ':
  case '\r':
  case '\t':
    // ignore whitespace
    break;
  case '\n':
    ++line;
    break;
  case '\'':
    scanOneCharacter();
    break;
  case '"':
    scanString();
    break;
  case '0':
    if (matchAndAdvance('x')) {
      scanHexadecimalNumber();
      break;
    }
  default: {
    if (isDigit(c)) {
      scanNumber();
    } else if (isAlpha(c)) {
      scanIdentifier();
    } else {
      std::string errorMessage = "Unexpected character. " + c;
      reportLexerError(errorMessage);
      break;
    }
  }
  }
}

void DoneLexer::scanIdentifier() {
  while (isAlphaNumeric(getCurrentChar()))
    advanceAndGetChar();
  const size_t identifierLength = current - start;
  const std::string identifier = source.substr(start, identifierLength);

  const bool isReservedKeyword =
      reservedKeywords.find(identifier) != reservedKeywords.end();

  if (isReservedKeyword) {
    addToken(reservedKeywords[identifier]);
  } else {
    addToken(TokenType::IDENTIFIER);
  }
}

void DoneLexer::scanNumber() {
  char c = getCurrentChar();
  while (isDigit(c) || c == '_') {
    advanceAndGetChar();
    c = getCurrentChar();
  }

  if (getCurrentChar() == '.' && isDigit(getNextChar())) {
    advanceAndGetChar();
    while (isDigit(getCurrentChar())) {
      advanceAndGetChar();
    }
  }

  const size_t numberLength = current - start;
  std::string numberLiteral = source.substr(start, numberLength);
  numberLiteral.erase(
      std::remove(numberLiteral.begin(), numberLiteral.end(), '_'),
      numberLiteral.end());
  addToken(TokenType::NUMBER, numberLiteral);
}

void DoneLexer::scanHexadecimalNumber() {
  char c = getCurrentChar();
  while (isHexDigit(c) || c == '_') {
    advanceAndGetChar();
    c = getCurrentChar();
  }

  const size_t numberLength = current - start;
  std::string numberLiteral = source.substr(start, numberLength);
  numberLiteral.erase(
      std::remove(numberLiteral.begin(), numberLiteral.end(), '_'),
      numberLiteral.end());
  addToken(TokenType::NUMBER, numberLiteral);
}

void DoneLexer::scanOneCharacter() {
  while (getCurrentChar() != '\'' && !isAtEnd()) {
    advanceAndGetChar();
  }
  if (isAtEnd()) {
    std::string errorMessage = "Unterminated string.";
    reportLexerError(errorMessage);
    return;
  }
  advanceAndGetChar();
  const size_t stringSize = current - start;
  const std::string stringLiteral = source.substr(start, stringSize);

  if (stringLiteral.size() != 3) {
    std::string errorMessage = "Character size must be one digit.";
    reportLexerError(errorMessage);
    return;
  }

  addToken(TokenType::CHAR, stringLiteral);
}

void DoneLexer::scanString() {
  while (getCurrentChar() != '"' && !isAtEnd()) {
    if (getCurrentChar() == '\n')
      ++line;
    advanceAndGetChar();
  }
  if (isAtEnd()) {
    std::string errorMessage = "Unterminated string.";
    reportLexerError(errorMessage);
    return;
  }

  advanceAndGetChar();
  const size_t stringSize = current - start;
  const std::string stringLiteral = source.substr(start, stringSize);
  addToken(TokenType::STRING, stringLiteral);
}

void DoneLexer::addToken(TokenType aTokenType, const std::string &value) {
  const size_t lexemeSize = current - start;
  const auto lexeme = source.substr(start, lexemeSize);
  tokens.emplace_back(aTokenType, lexeme, value, line, start, current);
}

void DoneLexer::addToken(TokenType tokenType) { addToken(tokenType, ""); }

void DoneLexer::reportLexerError(std::string errorMessage) {
  std::string errorPosition = std::to_string(getCurrentChar());
  Error error(currentFile, line, start, current, std::move(errorMessage),
              errorPosition);
  errorHandler.addError(error);
}

bool DoneLexer::matchAndAdvance(char c) {
  if (isAtEnd()) {
    return false;
  }
  if (source[current] != c) {
    return false;
  }
  ++current;
  return true;
}

char DoneLexer::getCurrentChar() {
  if (isAtEnd())
    return '\0';
  return source[current];
}

char DoneLexer::getNextChar() {
  if (current + 1 >= source.length())
    return '\0';
  return source[current + 1];
}

bool DoneLexer::isDigit(char c) { return c >= '0' && c <= '9'; }

bool DoneLexer::isHexDigit(char c) {
  if (isDigit(c))
    return true;
  else if (c >= 'a' && c <= 'f')
    return true;
  else if (c >= 'A' && c <= 'F')
    return true;
  return false;
}

bool DoneLexer::isAlpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool DoneLexer::isAlphaNumeric(char c) { return isAlpha(c) || isDigit(c); }

bool DoneLexer::isAtEnd() { return current >= source.size(); }
