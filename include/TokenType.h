#ifndef DONELANG_TOKENTYPE_H
#define DONELANG_TOKENTYPE_H

enum TokenType {
  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_BRACE,
  RIGHT_BRACE,
  ARRAY_LEFT_BRACKET,
  ARRAY_RIGHT_BRACKET,

  BANG,
  BANG_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,

  DOT,
  COMMA,
  COLON,
  COLON_EQUAL,
  COLON_COLON,
  SEMICOLON,
  ADDRESS,
  STAR_STAR,

  // Special assignments
  PLUS_EQUAL,
  MINUS_EQUAL,
  STAR_EQUAL,
  SLASH_EQUAL,
  STAR_STAR_EQUAL,

  // Logical Expressions
  OR,
  AND,
  XOR,

  // Keywords
  IMPORT,
  INCLUDE,
  FUN,
  VAR,
  CONST,
  RETURN,
  IDENTIFIER,
  IF,
  ELSE,
  ELSE_IF,
  FOR,
  DO,
  WHILE,
  TERNARY,
  ELVIS,
  CONTINUE,
  BREAK,
  LAMBDA,

  // Math Operations
  MINUS,
  PLUS,
  SLASH,
  STAR,
  PERCENT,

  // Unary Operations
  PLUS_PLUS,
  MINUS_MINUS,

  // Values
  TRUE,
  FALSE,
  NIL,
  VOID,

  // Data Types
  NUMBER,
  STRUCT,
  ENUM,
  BOOL,
  SHORT,
  INT,
  DOUBLE,
  FLOAT,
  CHAR,
  STRING,

  // Memory Management
  NEW,
  FREE,

  // End of File
  END_OF_FILE
};

#endif
