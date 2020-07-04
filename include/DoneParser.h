#ifndef DONELANG_DONEPARSER_H
#define DONELANG_DONEPARSER_H

#include <vector>
#include <memory>

#include "Token.h"
#include "Statement.h"
#include "Expression.h"
#include "ErrorHandler.h"

#define MAX_NUM_OF_ARGUMENTS 127

class DoneParser {
public:
    DoneParser(std::vector<Token> tokens, ErrorHandler &errorHandler);
    std::vector<Statement*> parseSourceCode();

private:
    int currentTokenIndex;
    std::vector<Token> tokens;
    ErrorHandler& errorHandler;

    Statement* parseStatement();
    Statement* parseDeclaration();
    Statement* parseEnumerationDeclaration();
    Statement* parseVarDeclaration();
    Statement* parseStructDeclaration();
    Statement* parseExpressionStatement();
    Statement* parseFuncDeclaration();
    Statement* parseIfStatement();

    /*
    Statement* parseBlockStatement();
    Statement* parseForStatement();
    Statement* parseWhileStatement();
    Statement* parseDoWhileStatement();
    */

    Expression* parseExpression();
    Expression* parseAssignExpression();
    //Expression parseNewExpression();
    //Expression parseFreeExpression();
    Expression* parsePrimaryExpression();
    Expression* parseCallExpression();
    Expression* parseFunctionCallExpression(Expression* callee);
    Expression* parseOrExpression();
    Expression* parseXorExpression();
    Expression* parseAndExpression();

    bool matchType(TokenType types);
    bool checkType(TokenType type);
    Token advance();
    Token getCurrentToken();
    void  pointNextToken();
    void  pointPreviousToken();
    Token getNextToken();
    Token getPreviousToken();
    Token consume(TokenType type, const char *message);
    void reportParserError(const std::string& message);
    bool isAtEnd();
};
#endif