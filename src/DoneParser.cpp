#include <iostream>

#include "../include/DoneParser.h"
#include "../include/FileManager.h"

#include "../include/Expressions.h"
#include "../include/Parameter.h"
#include "../include/Statements.h"

DoneParser::DoneParser(CompilerContext *context, DoneLexer *lexer)
    : context(context), lexer(lexer) {
  currentTokenIndex = 0;
  tokens = lexer->scanSourceCode();
}

std::vector<Statement *> DoneParser::parseSourceCode() {
  std::vector<Statement *> statements;
  while (!isAtEnd()) {
    if (matchType(INCLUDE)) {
      parseIncludeStatements();
      continue;
    }

    if (matchType(IMPORT)) {
      parseImportStatements(statements);
      continue;
    }

    statements.push_back(parseDeclaration());
  }
  return statements;
}

void DoneParser::parseImportStatements(std::vector<Statement *> &statements) {
  if (checkType(STRING)) {
    parseImportStatement(statements);
    return;
  }

  if (matchType(LEFT_BRACE)) {
    while (!matchType(RIGHT_BRACE)) {
      parseImportStatement(statements);
    }
    return;
  }

  std::cerr << "Expect string or { after import keyword." << std::endl;
}

void DoneParser::parseImportStatement(std::vector<Statement *> &statements) {
  Token name = consume(STRING, "Expect done source file path to import");
  std::string sourceFileName = name.lexeme.substr(1, name.lexeme.length() - 2);
  if (context->scannedFiles.count(sourceFileName) == 0) {
    context->scannedFiles.insert(sourceFileName);
    std::string sourceFilePath =
        context->projectPath + "/" + sourceFileName + ".done";
    std::string sourceCode = readFileContent(sourceFilePath);
    DoneLexer sourceLexer = DoneLexer(sourceCode, context->errorHandler);
    DoneParser sourceParser = DoneParser(context, &sourceLexer);
    std::vector<Statement *> subStatements = sourceParser.parseSourceCode();
    statements.insert(statements.end(), subStatements.begin(),
                      subStatements.end());
  } else {
    std::cerr << "This source file is already imported" << std::endl;
  }
}

void DoneParser::parseIncludeStatements() {
  if (checkType(STRING)) {
    parseIncludeStatement();
    return;
  }

  if (matchType(LEFT_BRACE)) {
    while (!matchType(RIGHT_BRACE)) {
      parseIncludeStatement();
    }
    return;
  }

  std::cerr << "Expect string or { after include keyword." << std::endl;
}

void DoneParser::parseIncludeStatement() {
  Token name = consume(STRING, "Expect library name to include");
  std::string moduleName = name.lexeme;
  std::string libraryName =
      moduleName.substr(1, moduleName.length() - 2) + ".h";
  if (context->cStdLibraries.count(moduleName) == 0) {
    context->cStdLibraries.insert(libraryName);
  } else {
    std::cerr << "This module is already imported" << std::endl;
  }
}

Statement *DoneParser::parseStatement() {
  if (matchType(IF))
    return parseIfStatement();
  if (matchType(DO))
    return parseDoWhileStatement();
  if (matchType(WHILE))
    return parseWhileStatement();
  if (matchType(RETURN))
    return parseReturnStatement();
  if (matchType(LEFT_BRACE))
    return parseBlockStatement();
  return parseExpressionStatement();
}

Statement *DoneParser::parseDeclaration() {
  if (matchType(FUN))
    return parseFuncDeclaration();
  if (matchType(VAR))
    return parseVarDeclaration(false);
  if (matchType(CONST))
    return parseVarDeclaration(true);
  if (matchType(ENUM))
    return parseEnumerationDeclaration();
  if (matchType(STRUCT))
    return parseStructDeclaration();
  return parseStatement();
}

Statement *DoneParser::parseVarDeclaration(bool isConst) {
  Token name = consume(IDENTIFIER, "Expect var name");
  consume(COLON, "Expect : after var name");
  MemoryType memoryType = parseMemoryType();
  Token type = consume(IDENTIFIER, "Expect Variable type");
  bool isInitialized = false;
  bool isArrayStatement = false;
  Expression *arraySize = nullptr;
  if (matchType(ARRAY_LEFT_BRACKET)) {
    isArrayStatement = true;
    if (!matchType(ARRAY_RIGHT_BRACKET)) {
      arraySize = parseExpression();
      consume(ARRAY_RIGHT_BRACKET, "Expect ] after array size");
    }
    if (matchType(ARRAY_LEFT_BRACKET)) {
      // TODO: 2D array ^_^
    }
  }
  Expression *value = nullptr;
  if (matchType(EQUAL)) {
    value = parseExpression();
    isInitialized = true;
    consume(SEMICOLON, "Expect ; after init type");
  } else {
    consume(SEMICOLON, "Expect ; after Declare type");
  }

  if (isArrayStatement) {
    return new ArrayStatement(name, type, arraySize, memoryType, isInitialized,
                              value);
  }
  return new VarStatement(name, type, memoryType, isInitialized, value,
                          isConst);
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
    MemoryType memoryType = NONE;
    Token varType = consume(IDENTIFIER, "Expect struct var type");
    consume(SEMICOLON, "Expect ; after var declaration");
    bool isArrayType = false;
    if (matchType(ARRAY_LEFT_BRACKET)) {
      consume(ARRAY_RIGHT_BRACKET, "Expect ] after array Declaration");
      isArrayType = true;
    }
    fields.push_back(Parameter(varName, varType, memoryType, isArrayType));
  }
  consume(RIGHT_BRACE, "Expect : } after struct name");
  return new StructStatement(name, fields);
}

Statement *DoneParser::parseBlockStatement() {
  std::vector<Statement *> statements;
  while (!matchType(RIGHT_BRACE)) {
    statements.push_back(parseDeclaration());
  }
  return new BlockStatement(statements);
}

Statement *DoneParser::parseExpressionStatement() {
  Expression *expression = parseExpression();
  consume(SEMICOLON, "Expect ; after Expression");
  return new ExpressionStatement(expression);
}

Statement *DoneParser::parseFuncDeclaration() {
  Token name = consume(IDENTIFIER, "Expect function name");
  consume(LEFT_PAREN, "Expect : ( after function name");

  std::vector<Parameter> params;

  if (matchType(IDENTIFIER)) {
    pointPreviousToken();
    Token paramName = consume(IDENTIFIER, "Expect parameter name");
    consume(COLON, "Expect : after param name");
    MemoryType memoryType = parseMemoryType();
    Token typeName = consume(IDENTIFIER, "Expect function name");
    bool isArrayType = false;
    if (matchType(ARRAY_LEFT_BRACKET)) {
      consume(ARRAY_RIGHT_BRACKET, "Expect ] after array Declaration");
      isArrayType = true;
    }
    params.emplace_back(paramName, typeName, memoryType, isArrayType);
  }

  while (matchType(COMMA)) {
    pointPreviousToken();
    consume(COMMA, "Expect , after next param name");
    Token paramName = consume(IDENTIFIER, "Expect function name");
    consume(COLON, "Expect : after param name");
    MemoryType memoryType = parseMemoryType();
    Token typeName = consume(IDENTIFIER, "Expect function name");
    bool isArrayType = false;
    if (matchType(ARRAY_LEFT_BRACKET)) {
      consume(ARRAY_RIGHT_BRACKET, "Expect ] after array Declaration");
      isArrayType = true;
    }
    params.emplace_back(paramName, typeName, memoryType, isArrayType);
  }

  consume(RIGHT_PAREN, "Expect : ) after function name");
  consume(COLON, "Expect : after function Params");
  Token returnType = consume(IDENTIFIER, "Expect return type");

  if (matchType(LAMBDA)) {
    Statement *statement = parseStatement();
    return new LineFunctionStatement(name, returnType, params, statement);
  }

  consume(LEFT_BRACE, "Expect : { after struct name");

  std::vector<Statement *> body;
  while (!matchType(RIGHT_BRACE)) {
    if (matchType(VAR)) {
      body.push_back(parseVarDeclaration(false));
    } else if (matchType(CONST)) {
      body.push_back(parseVarDeclaration(true));
    } else {
      body.push_back(parseStatement());
    }
  }

  return new FunctionStatement(name, returnType, params, body);
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

  // Else if Statements if exists
  std::vector<ElseIfStatement *> elseIfStatements;
  while (matchType(ELSE_IF)) {
    consume(LEFT_PAREN, "Expect : ( after else if keyword");
    Expression *elseIfCondition = parseExpression();
    consume(RIGHT_PAREN, "Expect : ) after else if condition");
    consume(LEFT_BRACE, "Expect : { after to start else if body");

    std::vector<Statement *> elseIfBody;
    while (!matchType(RIGHT_BRACE)) {
      elseIfBody.push_back(parseDeclaration());
    }

    elseIfStatements.push_back(
        new ElseIfStatement(elseIfCondition, elseIfBody));
  }

  // Else Statement if exists
  ElseStatement *elseStatement = nullptr;
  if (matchType(ELSE)) {
    consume(LEFT_BRACE, "Expect : { after to start if body");

    std::vector<Statement *> elseBody;
    while (!matchType(RIGHT_BRACE)) {
      elseBody.push_back(parseDeclaration());
    }

    elseStatement = new ElseStatement(elseBody);
  }

  return new IfStatement(condition, body, elseIfStatements, elseStatement);
}

Statement *DoneParser::parseWhileStatement() {
  consume(LEFT_PAREN, "Expect : ( after while keyword");
  Expression *condition = parseExpression();
  consume(RIGHT_PAREN, "Expect : ) after while condition");
  consume(LEFT_BRACE, "Expect : { after to start while body");

  std::vector<Statement *> body;
  while (!matchType(RIGHT_BRACE)) {
    body.push_back(parseDeclaration());
  }
  return new WhileStatement(condition, body);
}

Statement *DoneParser::parseDoWhileStatement() {
  consume(LEFT_BRACE, "Expect : { after to start while body");
  std::vector<Statement *> body;
  while (!matchType(RIGHT_BRACE)) {
    body.push_back(parseDeclaration());
  }
  consume(WHILE, "Expect : while keyword after do block");
  consume(LEFT_PAREN, "Expect : ( after while keyword");
  Expression *condition = parseExpression();
  consume(RIGHT_PAREN, "Expect : ) after while condition");
  consume(SEMICOLON, "Expect : ; after while condition");
  return new DoWhileStatement(condition, body);
}

Statement *DoneParser::parseReturnStatement() {
  if (matchType(SEMICOLON)) {
    return new ReturnStatement(nullptr);
  }
  Expression *expression = parseExpression();
  consume(SEMICOLON, "Expect ; after return statement");
  return new ReturnStatement(expression);
}

Expression *DoneParser::parseExpression() { return parseAssignExpression(); }

Expression *DoneParser::parseAssignExpression() {
  MemoryType type = parseMemoryType();
  Expression *expression = parseTernaryExpression();
  if (matchType(EQUAL)) {
    Expression *value = parseAssignExpression();
    consume(SEMICOLON, "Expect ; after Assign Expression");
    return new AssignExpression(expression, value, type);
  }
  return expression;
}

Expression *DoneParser::parseTernaryExpression() {
  Expression *expression = parseElvisExpression();
  if (matchType(TERNARY)) {
    Expression *truthExpr = parseExpression();
    consume(COLON, "Expect : after first Expression");
    Expression *falseExpr = parseExpression();
    return new TernaryExpression(expression, truthExpr, falseExpr);
  }
  return expression;
}

Expression *DoneParser::parseElvisExpression() {
  Expression *expression = parseOrExpression();
  if (matchType(ELVIS)) {
    Expression *falseExpr = parseExpression();
    return new TernaryExpression(expression, expression, falseExpr);
  }
  return expression;
}

Expression *DoneParser::parseOrExpression() {
  Expression *expression = parseXorExpression();
  if (matchType(OR)) {
    Token opt = getPreviousToken();
    Expression *right = parseXorExpression();
    return new LogicalExpression(expression, right, opt);
  }
  return expression;
}

Expression *DoneParser::parseXorExpression() {
  Expression *expression = parseAndExpression();
  if (matchType(XOR)) {
    Token opt = getPreviousToken();
    Expression *right = parseAndExpression();
    return new LogicalExpression(expression, right, opt);
  }
  return expression;
}

Expression *DoneParser::parseAndExpression() {
  Expression *expression = parseEqualityExpression();
  if (matchType(AND)) {
    Token opt = getPreviousToken();
    Expression *right = parseEqualityExpression();
    return new LogicalExpression(expression, right, opt);
  }
  return expression;
}

Expression *DoneParser::parseEqualityExpression() {
  Expression *expression = parseComparisonExpression();
  while (matchType(EQUAL_EQUAL) || matchType(BANG_EQUAL)) {
    Token opt = getPreviousToken();
    Expression *right = parseComparisonExpression();
    expression = new BinaryExpression(right, expression, opt);
  }
  return expression;
}

Expression *DoneParser::parseComparisonExpression() {
  Expression *expression = parseAdditionExpression();
  while (matchType(GREATER) || matchType(GREATER_EQUAL) || matchType(LESS) ||
         matchType(LESS_EQUAL)) {
    Token opt = getPreviousToken();
    Expression *right = parseAdditionExpression();
    expression = new BinaryExpression(right, expression, opt);
  }
  return expression;
}

Expression *DoneParser::parseAdditionExpression() {
  Expression *expression = parseMultiplicationExpression();
  while (matchType(PLUS) || matchType(MINUS)) {
    Token opt = getPreviousToken();
    Expression *right = parseMultiplicationExpression();
    expression = new BinaryExpression(right, expression, opt);
  }
  return expression;
}

Expression *DoneParser::parseMultiplicationExpression() {
  Expression *expression = parseUnaryExpression();
  while (matchType(STAR) || matchType(SLASH) || matchType(PERCENT)) {
    Token opt = getPreviousToken();
    Expression *right = parseUnaryExpression();
    expression = new BinaryExpression(right, expression, opt);
  }
  return expression;
}

Expression *DoneParser::parseUnaryExpression() {
  if (matchType(BANG) || matchType(MINUS) || matchType(PLUS_PLUS) ||
      matchType(MINUS_MINUS)) {
    Token opt = getPreviousToken();
    Expression *right = parseUnaryExpression();
    return new UnaryExpression(opt, right);
  }
  return parseCallExpression();
}

Expression *DoneParser::parseCallExpression() {
  Expression *expression = parsePrimaryExpression();
  while (true) {
    if (matchType(LEFT_PAREN)) {
      expression = parseFunctionCallExpression(expression);
    } else if (matchType(DOT)) {
      Token name = consume(IDENTIFIER, "Expect property name after '.'.");
      expression = new GetExpression(name, expression);
    } else {
      break;
    }
  }
  return expression;
}

Expression *DoneParser::parseFunctionCallExpression(Expression *callee) {
  std::vector<Expression *> arguments;
  if (!checkType(RIGHT_PAREN)) {
    do {
      if (arguments.size() >= MAX_NUM_OF_ARGUMENTS) {
        reportParserError("Number of arguments must be less than or equal 127");
      }
      arguments.push_back(parseExpression());
    } while (matchType(COMMA));
  }
  consume(RIGHT_PAREN, "Expect ) after function call");
  return new CallExpression(callee, arguments);
}

Expression *DoneParser::parseArrayValuesExpression() {
  std::vector<Expression *> values;
  if (!matchType(RIGHT_BRACE)) {
    do {
      values.push_back(parseExpression());
    } while (matchType(COMMA));
  }
  consume(RIGHT_BRACE, "Expect } in the end of the array");
  return new ArrayValuesExpression(values);
}

Expression *DoneParser::parsePrimaryExpression() {
  if (matchType(TRUE))
    return new LiteralExpression("true");
  if (matchType(FALSE))
    return new LiteralExpression("false");
  if (matchType(NIL))
    return new LiteralExpression("NULL");
  if (matchType(NUMBER))
    return new LiteralExpression(getPreviousToken().literal);
  if (matchType(STRING))
    return new LiteralExpression(getPreviousToken().literal);
  if (matchType(CHAR))
    return new LiteralExpression(getPreviousToken().literal);
  if (matchType(CONTINUE))
    return new LiteralExpression("continue");
  if (matchType(BREAK))
    return new LiteralExpression("break");
  if (matchType(IDENTIFIER)) {
    MemoryType memoryType = NONE;
    if (currentTokenIndex - 2 >= 0) {
      memoryType = parseMemoryType(tokens[currentTokenIndex - 2]);
    }
    if (getCurrentToken().tokenType == ARRAY_LEFT_BRACKET) {
      auto *variable = new VariableExpression(getPreviousToken(), memoryType);
      consume(ARRAY_LEFT_BRACKET, "Expect [ after array position");
      Expression *index = parseExpression();
      consume(ARRAY_RIGHT_BRACKET, "Expect ] after array position");
      return new ArrayExpression(variable, index);
    }
    return new VariableExpression(getPreviousToken(), memoryType);
  }
  if (matchType(LEFT_PAREN)) {
    Expression *expr = parseExpression();
    consume(RIGHT_PAREN, "Expect ')' after expression.");
    return new GroupExpression(expr);
  }
  if (matchType(LEFT_BRACE)) {
    return parseArrayValuesExpression();
  }
  synchronize();
  return nullptr;
}

MemoryType DoneParser::parseMemoryType() {
  MemoryType type = NONE;
  if (matchType(STAR))
    type = SINGLE_POINTER;
  else if (matchType(STAR_STAR))
    type = DOUBLE_POINTER;
  else if (matchType(ADDRESS))
    type = ADDRESS_POINTER;
  return type;
}

MemoryType DoneParser::parseMemoryType(Token &token) {
  if (token.tokenType == STAR)
    return SINGLE_POINTER;
  if (token.tokenType == STAR_STAR)
    return DOUBLE_POINTER;
  if (token.tokenType == ADDRESS)
    return ADDRESS_POINTER;
  return NONE;
}

bool DoneParser::matchType(TokenType types) {
  if (checkType(types)) {
    advance();
    return true;
  }
  return false;
}

bool DoneParser::checkType(TokenType type) {
  if (isAtEnd())
    return false;
  return getCurrentToken().tokenType == type;
}

Token DoneParser::advance() {
  if (!isAtEnd())
    currentTokenIndex++;
  return getPreviousToken();
}

Token DoneParser::getCurrentToken() { return tokens[currentTokenIndex]; }

Token DoneParser::getNextToken() { return tokens[currentTokenIndex + 1]; }

Token DoneParser::getPreviousToken() { return tokens[currentTokenIndex - 1]; }

void DoneParser::pointNextToken() {
  if (isAtEnd()) {
    currentTokenIndex = currentTokenIndex + 1;
  }
}

void DoneParser::pointPreviousToken() {
  if (currentTokenIndex > 0) {
    currentTokenIndex = currentTokenIndex - 1;
  }
}

Token DoneParser::consume(TokenType type, const char *message) {
  if (checkType(type))
    return advance();
  reportParserError(message);
  synchronize();
}

void DoneParser::reportParserError(const std::string &message) {
  Token token = getCurrentToken();
  context->errorHandler.addError(Error(token, message));
  synchronize();
  context->errorHandler.report();
  exit(EXIT_FAILURE);
}

bool DoneParser::isAtEnd() {
  return getCurrentToken().tokenType == END_OF_FILE;
}

Token DoneParser::getNextTokenBy(int offset) {
  return tokens[currentTokenIndex + offset];
}

Token DoneParser::getPreviousTokenBy(int offset) {
  return tokens[currentTokenIndex - offset];
}

void DoneParser::synchronize() {
  advance();

  while (!isAtEnd()) {
    if (getPreviousToken().tokenType == SEMICOLON)
      return;
    switch (getNextToken().tokenType) {
    case FUN:
    case VAR:
    case CONST:
    case FOR:
    case IF:
    case DO:
    case WHILE:
    case RETURN:
      return;
    }
    advance();
  }
}
