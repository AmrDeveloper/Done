#ifndef DONELANG_DONEPARSER_H
#define DONELANG_DONEPARSER_H

#include <vector>
#include <memory>

#include "Token.h"
#include "Statements.h"
#include "Expressions.h"
#include "ErrorHandler.h"
#include "CompilerContext.h"
#include "DoneLexer.h"

#define MAX_NUM_OF_ARGUMENTS 127

class DoneParser {
public:
    DoneParser(CompilerContext* context, DoneLexer* lexer);
    std::vector<Statement*> parseSourceCode();

private:
    int currentTokenIndex;
    std::vector<Token> tokens;
    CompilerContext* context;
    DoneLexer* lexer;

    void parseImportStatements(std::vector<Statement*>&);
    void parseImportStatement(std::vector<Statement*>&);
    void parseIncludeStatements();
    void parseIncludeStatement();

    Statement* parseStatement();
    Statement* parseDeclaration();
    Statement* parseEnumerationDeclaration();
    Statement* parseVarDeclaration(bool isConst);
    Statement* parseStructDeclaration();
    Statement* parseExpressionStatement();
    Statement* parseFuncDeclaration();
    Statement* parseIfStatement();
    Statement* parseBlockStatement();
    Statement* parseWhileStatement();
    Statement* parseDoWhileStatement();
    Statement* parseReturnStatement();

    Expression* parseExpression();
    Expression* parseAssignExpression();
    Expression* parsePrimaryExpression();
    Expression* parseCallExpression();
    Expression* parseFunctionCallExpression(Expression* callee);
    Expression* parseOrExpression();
    Expression* parseXorExpression();
    Expression* parseAndExpression();
    Expression* parseTernaryExpression();
    Expression* parseElvisExpression();
    Expression* parseEqualityExpression();
    Expression* parseComparisonExpression();
    Expression* parseAdditionExpression();
    Expression* parseMultiplicationExpression();
    Expression* parseUnaryExpression();
    Expression* parseArrayValuesExpression();

    void synchronize();
    bool matchType(TokenType types);
    bool checkType(TokenType type);
    Token advance();
    Token getCurrentToken();
    void  pointNextToken();
    void  pointPreviousToken();
    Token getNextToken();
    Token getPreviousToken();
    Token getNextTokenBy(int offset);
    Token getPreviousTokenBy(int offset);
    MemoryType parseMemoryType();
    MemoryType parseMemoryType(Token& token);
    Token consume(TokenType type, const char *message);
    void reportParserError(const std::string& message);
    bool isAtEnd();
};
#endif