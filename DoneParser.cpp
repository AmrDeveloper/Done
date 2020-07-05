#include "include/DoneParser.h"

#include "include/EnumStatement.h"
#include "include/VarStatement.h"
#include "include/StructStatement.h"
#include "include/ExpressionStatement.h"
#include "include/FunctionStatement.h"
#include "include/IfStatement.h"
#include "include/Parameter.h"

#include "include/LiteralExpression.h"
#include "include/AssignExpression.h"
#include "include/CallExpression.h"
#include "include/VariableExpression.h"
#include "include/GroupExpression.h"
#include "include/LogicalExpression.h"
#include "include/GetExpression.h"
#include "include/TernaryExpression.h"
#include "include/BinaryExpression.h"
#include "include/UnaryExpression.h"

#include <iostream>

DoneParser::DoneParser(std::vector<Token> tokens, ErrorHandler &errorHandler)
        : tokens(std::move(tokens)), errorHandler(errorHandler) {
    currentTokenIndex = 0;
}

std::vector<Statement*> DoneParser::parseSourceCode() {
    std::vector<Statement*> statements;
    while (!isAtEnd()) {
        statements.push_back(parseDeclaration());
    }
    return statements;
}

Statement *DoneParser::parseStatement() {
    if (matchType(IF)) return parseIfStatement();
    //if(matchType(FOR)) return parseForStatement();
    //if(matchType(DO)) return parseDoWhileStatement();
    //if(matchType(WHILE)) return parseWhileStatement();
    //if(matchType(LEFT_BRACE)) return parseBlockStatement();
    return parseExpressionStatement();
}

Statement *DoneParser::parseDeclaration() {
    if (matchType(FUN)) return parseFuncDeclaration();
    if (matchType(VAR)) return parseVarDeclaration();
    if (matchType(ENUM)) return parseEnumerationDeclaration();
    if (matchType(STRUCT)) return parseStructDeclaration();
    return parseStatement();
}

Statement *DoneParser::parseVarDeclaration() {
    Token name = consume(IDENTIFIER, "Expect var name");
    consume(COLON, "Expect : after var name");
    bool isPointer = matchType(STAR);
    Token type = consume(IDENTIFIER, "Expect Type type");
    if (matchType(EQUAL)) {
        Expression *value = parseExpression();
        consume(SEMICOLON, "Expect ; after init type");
        return new VarStatement(name, type, isPointer, true, value);
    } else {
        consume(SEMICOLON, "Expect ; after Declare type");
        return new VarStatement(name, type, isPointer, false, nullptr);
    }
}

Statement *DoneParser::parseEnumerationDeclaration() {
    Token name = consume(IDENTIFIER, "Expect Enum name");
    consume(LEFT_BRACE, "Expect { after enum name");

    std::vector<Token> fields;

    if (checkType(IDENTIFIER)) {
        Token field = consume(IDENTIFIER, "Expect Enum name");
        fields.push_back(field);
    }

    while (matchType(RIGHT_BRACE) == 0) {
        consume(COMMA, "Expect { after enum name");
        Token field = consume(IDENTIFIER, "Expect Enum name");
        fields.push_back(field);
    }

    return new EnumStatement(name, fields);
}

Statement *DoneParser::parseStructDeclaration() {
    Token name = consume(IDENTIFIER, "Expect struct name");
    consume(LEFT_BRACE, "Expect : { after struct name");
    std::vector<Parameter> fields;
    while (matchType(VAR)) {
        Token varName = consume(IDENTIFIER, "Expect struct var name");
        consume(COLON, "Expect struct name");
        bool isPointer = false;
        Token varType = consume(IDENTIFIER, "Expect struct var type");
        consume(SEMICOLON, "Expect ; after var declaration");
        fields.push_back(Parameter(varName, varType, isPointer));
    }
    consume(RIGHT_BRACE, "Expect : } after struct name");
    return new StructStatement(name, fields);
}

Statement *DoneParser::parseExpressionStatement() {
    return new ExpressionStatement(parseExpression());
}

Statement *DoneParser::parseFuncDeclaration() {
    Token name = consume(IDENTIFIER, "Expect function name");
    consume(LEFT_PAREN, "Expect : ( after function name");

    std::vector<Parameter> params;

    if (matchType(IDENTIFIER)) {
        pointPreviousToken();
        Token paramName = consume(IDENTIFIER, "Expect function name");
        consume(COLON, "Expect : after param name");
        bool isPointer = matchType(STAR);
        Token typeName = consume(IDENTIFIER, "Expect function name");
        params.push_back(Parameter(paramName, typeName, isPointer));
    }

    while (matchType(COMMA)) {
        pointPreviousToken();
        consume(COMMA, "Expect , after next param name");
        Token paramName = consume(IDENTIFIER, "Expect function name");
        consume(COLON, "Expect : after param name");
        bool isPointer = matchType(STAR);
        Token typeName = consume(IDENTIFIER, "Expect function name");
        params.push_back(Parameter(paramName, typeName, isPointer));
    }

    consume(RIGHT_PAREN, "Expect : ) after function name");
    consume(COLON, "Expect : after function Params");
    Token returnType = consume(IDENTIFIER, "Expect return type");
    consume(LEFT_BRACE, "Expect : { after struct name");

    std::vector<Statement *> body;
    Expression *returnValue = nullptr;
    while (!matchType(RIGHT_BRACE)) {
        if (returnType.tokenType != VOID && matchType(RETURN)) {
            returnValue = parseExpression();
            consume(SEMICOLON, "Expect ; after return name");
            break;
        }
        else if(matchType(VAR)) {
            body.push_back(parseVarDeclaration());
        }
        else{
            body.push_back(parseStatement());
        }
    }
    consume(RIGHT_BRACE, "Expect } after return name");
    return new FunctionStatement(name, returnType, params, body, returnValue);
}

Statement *DoneParser::parseIfStatement() {
    consume(LEFT_PAREN, "Expect : ( after if keyword");
    Expression *condition = parseExpression();
    consume(RIGHT_PAREN, "Expect : ) after if condition");
    consume(LEFT_BRACE, "Expect : { after to start if body");

    std::vector<Statement *> body;
    while (!matchType(RIGHT_BRACE)) {
        body.push_back(parseDeclaration());
    }
    return new IfStatement(condition, body);
}

Expression *DoneParser::parseExpression() {
    return parseAssignExpression();
}

Expression *DoneParser::parseAssignExpression() {
    //TODO : must fix it to support SetExp
    if(getNextToken().tokenType == EQUAL || checkType(ADDRESS)) {
        bool isPointer = matchType(ADDRESS);
        Token name = consume(IDENTIFIER, "Expect variable name");
        consume(EQUAL, "Expect equal");
        Expression* value = parseAssignExpression();
        consume(SEMICOLON, "Expect ; after Assign Expression");
        return new AssignExpression(name, value, isPointer);
    }
    return parseTernaryExpression();
}

Expression *DoneParser::parseTernaryExpression() {
    Expression* expression = parseElvisExpression();
    if(matchType(TERNARY)) {
        Expression* truthExpr = parseExpression();
        consume(COLON, "Expect : after first Expression");
        Expression* falseExpr = parseExpression();
        return new TernaryExpression(expression, truthExpr, falseExpr);
    }
    return expression;
}

Expression *DoneParser::parseElvisExpression() {
    Expression* expression = parseOrExpression();
    if(matchType(ELVIS)) {
        Expression* falseExpr = parseExpression();
        return new TernaryExpression(expression, expression, falseExpr);
    }
    return expression;
}

Expression *DoneParser::parseOrExpression() {
    Expression* expression = parseXorExpression();
    if(matchType(OR)) {
        Token opt = getPreviousToken();
        Expression* right = parseXorExpression();
        return new LogicalExpression(expression, right, opt);
    }
    return expression;
}

Expression *DoneParser::parseXorExpression() {
    Expression* expression = parseAndExpression();
    if(matchType(XOR)) {
        Token opt = getPreviousToken();
        Expression* right = parseAndExpression();
        return new LogicalExpression(expression, right, opt);
    }
    return expression;
}

Expression *DoneParser::parseAndExpression() {
    Expression* expression = parseEqualityExpression();
    if(matchType(AND)) {
        Token opt = getPreviousToken();
        Expression* right = parseEqualityExpression();
        return new LogicalExpression(expression, right, opt);
    }
    return expression;
}

Expression *DoneParser::parseEqualityExpression() {
    Expression* expression = parseComparisonExpression();
    while (matchType(EQUAL_EQUAL) || matchType(BANG_EQUAL)) {
        Token opt = getPreviousToken();
        Expression* right = parseComparisonExpression();
        expression = new BinaryExpression(right, expression, opt);
    }
    return expression;
}

Expression *DoneParser::parseComparisonExpression() {
    Expression* expression = parseAdditionExpression();
    while (matchType(GREATER) || matchType(GREATER_EQUAL)) {
        Token opt = getPreviousToken();
        Expression* right = parseAdditionExpression();
        expression = new BinaryExpression(right, expression, opt);
    }
    return expression;
}

Expression *DoneParser::parseAdditionExpression() {
    Expression* expression = parseMultiplicationExpression();
    while (matchType(PLUS) || matchType(MINUS)) {
        Token opt = getPreviousToken();
        Expression* right = parseMultiplicationExpression();
        expression = new BinaryExpression(right, expression, opt);
    }
    return expression;
}

Expression *DoneParser::parseMultiplicationExpression() {
    Expression* expression = parseUnaryExpression();
    while (matchType(STAR) || matchType(SLASH)) {
        Token opt = getPreviousToken();
        Expression* right = parseUnaryExpression();
        expression = new BinaryExpression(right, expression, opt);
    }
    return expression;
}

Expression *DoneParser::parseUnaryExpression() {
    if (matchType(BANG)
    || matchType(MINUS)
    || matchType(PLUS_PLUS)
    || matchType(MINUS_MINUS)) {
        Token opt = getPreviousToken();
        Expression* right = parseUnaryExpression();
        return new UnaryExpression(opt, right);
    }
    return parseCallExpression();
}

Expression *DoneParser::parseCallExpression() {
    Expression* expression = parsePrimaryExpression();
    while(true) {
        if(matchType(LEFT_PAREN)) {
            expression = parseFunctionCallExpression(expression);
        }
        else if(matchType(DOT)) {
            Token name = consume(IDENTIFIER, "Expect property name after '.'.");
            expression = new GetExpression(name, expression);
        }
        else{
            break;
        }
    }
    return expression;
}

Expression *DoneParser::parseFunctionCallExpression(Expression* callee) {
     std::vector<Expression*> arguments;
     if(!checkType(RIGHT_PAREN)) {
         do{
             if(arguments.size() >= MAX_NUM_OF_ARGUMENTS) {
                 reportParserError("Number of arguments must be less than or equal 127");
             }
             arguments.push_back(parseExpression());
         }while (matchType(COMMA));
     }
     consume(RIGHT_PAREN, "Expect ) after function call");
     consume(SEMICOLON, "Expect ; after Assign Expression");
     return new CallExpression(callee, arguments);
}

Expression *DoneParser::parsePrimaryExpression() {
    if (matchType(TRUE)) return new LiteralExpression("1");
    if (matchType(FALSE)) return new LiteralExpression("0");
    if (matchType(NIL)) return new LiteralExpression("null");
    if (matchType(NUMBER)) return new LiteralExpression(getPreviousToken().literal);
    if (matchType(STRING)) return new LiteralExpression(getPreviousToken().literal);
    if (matchType(CHAR)) return new LiteralExpression(getPreviousToken().literal);
    if (matchType(IDENTIFIER)) return new VariableExpression(getPreviousToken());
    if (matchType(LEFT_PAREN)) {
        Expression* expr = parseExpression();
        consume(RIGHT_PAREN, "Expect ')' after expression.");
        return new GroupExpression(expr);
    }
    std::cout<<"Invalid Token "<<getCurrentToken().lexeme;
    return nullptr;
}

bool DoneParser::matchType(TokenType types) {
    if(checkType(types)) {
        advance();
        return true;
    }
    return false;
}

bool DoneParser::checkType(TokenType type) {
    if(isAtEnd()) return false;
    return getCurrentToken().tokenType == type;
}

Token DoneParser::advance() {
    if(!isAtEnd()) currentTokenIndex++;
    return getPreviousToken();
}

Token DoneParser::getCurrentToken() {
    return tokens[currentTokenIndex];
}

Token DoneParser::getNextToken() {
    return tokens[currentTokenIndex + 1];
}

Token DoneParser::getPreviousToken() {
    return tokens[currentTokenIndex - 1];
}

void DoneParser::pointNextToken() {
    if(isAtEnd()) {
        currentTokenIndex = currentTokenIndex + 1;
    }
}

void DoneParser::pointPreviousToken() {
    if(currentTokenIndex > 0) {
        currentTokenIndex = currentTokenIndex - 1;
    }
}

Token DoneParser::consume(TokenType type, const char *message) {
    if(checkType(type)) return advance();
    reportParserError(message);
}

void DoneParser::reportParserError(const std::string& message) {
   std::cout<<message;
   exit(EXIT_FAILURE);
}

bool DoneParser::isAtEnd() {
    return getCurrentToken().tokenType == END_OF_FILE;
}
