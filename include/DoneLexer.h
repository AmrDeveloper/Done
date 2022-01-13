#ifndef DONELANG_DONELEXER_H
#define DONELANG_DONELEXER_H

#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#include "ErrorHandler.h"
#include "Token.h"

class DoneLexer {

public:
  DoneLexer(const std::string &aSource, ErrorHandler &aErrorHandler);
  std::vector<Token> scanSourceCode();

private:
  int line;
  int start;
  int current;
  std::string source;
  std::string currentFile;
  std::vector<Token> tokens;
  std::stack<std::string> dependencyFilesStack;
  std::unordered_map<std::string, TokenType> reservedKeywords;
  ErrorHandler &errorHandler;

  char advanceAndGetChar();
  void scanAndAddToken();
  void scanOneCharacter();
  void scanString();
  void scanNumber();
  void scanHexadecimalNumber();
  void scanIdentifier();
  void scanPreprocessorLabel();
  void addToken(TokenType tokenType);
  void addToken(TokenType tokenType, const std::string &value);
  bool matchAndAdvance(char c);
  char getCurrentChar();
  char getNextChar();
  static bool isDigit(char c);
  static bool isHexDigit(char c);
  static bool isAlpha(char c);
  static bool isAlphaNumeric(char c);
  void reportLexerError(std::string message);
  bool isAtEnd();
};

#endif
