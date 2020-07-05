#ifndef DONELANG_TOKENTYPE_H
#define DONELANG_TOKENTYPE_H

enum TokenType {
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,

    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    DOT, COMMA, COLON, COLON_EQUAL,
    COLON_COLON, SEMICOLON, ADDRESS,

    //Special assignments
    PLUS_EQUAL, MINUS_EQUAL, STAR_EQUAL, SLASH_EQUAL, STAR_STAR_EQUAL,

    //Logical Expressions
    OR, AND, XOR,

    //Keywords
    FUN, VAR, RETURN, IDENTIFIER, IMPORT,
    IF, ELSE, ELSE_IF, FOR, DO, WHILE,
    TERNARY, ELVIS, CONTINUE, BREAK,

    //Math Operations
    MINUS, PLUS, SLASH, STAR,

    //Unary Operations
    PLUS_PLUS, MINUS_MINUS,


    //Values
    TRUE, FALSE, NIL, VOID,

    //Data Types
    NUMBER, STRUCT, ENUM, BOOL, SHORT,
    INT, DOUBLE, FLOAT, CHAR, STRING,

    //Memory Management
    NEW, FREE,

    //End of File
    END_OF_FILE
};

#endif
