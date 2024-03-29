#include "../include/CodeGenerator.h"

using namespace std;

CodeGenerator::CodeGenerator(CompilerContext *context) : context(context) {}

std::string
CodeGenerator::generateCode(const std::vector<Statement *> &statements) {
  generateSourceCodeHeaders(context->cStdLibraries);
  for (auto statement : statements) {
    statement->accept(this);
  }
  return codeWriter.getSource();
}

void CodeGenerator::generateSourceCodeHeaders(
    const std::set<std::string> &libs) {
  for (auto library : context->cStdLibraries) {
    codeWriter.appendLine("#include<" + library + ">");
  }

  if (libs.find("stdbool") == libs.end()) {
    codeWriter.appendLine("#include<stdbool.h>");
  }

  codeWriter.appendLine("#define string char*");
}

void CodeGenerator::visit(EnumStatement *enumStatement) {
  codeWriter.append("typedef enum {");
  int fieldsSize = enumStatement->fields.size();
  for (int i = 0; i < fieldsSize; i++) {
    Token token = enumStatement->fields[i];
    codeWriter.append(token.lexeme);
    if (i != fieldsSize - 1) {
      codeWriter.append(",");
    }
  }
  codeWriter.appendLine("}" + enumStatement->name.lexeme + ";");
}

void CodeGenerator::visit(VarStatement *varStatement) {
  if (varStatement->isConst) {
    codeWriter.append("const ");
  }
  codeWriter.append(varStatement->type.lexeme + " ");
  MemoryType type = varStatement->memoryType;
  generateMemoryType(type);
  codeWriter.append(varStatement->name.lexeme);
  if (varStatement->isInitialized) {
    codeWriter.append("=");
    varStatement->value->accept(this);
  }
  codeWriter.appendLine(";");
}

void CodeGenerator::visit(StructStatement *structStatement) {
  codeWriter.appendLine("typedef struct{");
  for (Parameter field : structStatement->fields) {
    codeWriter.append(field.type.lexeme);
    generateMemoryType(field.memoryType);
    codeWriter.append(" " + field.name.lexeme);
    if (field.isArrayType) {
      codeWriter.append("[]");
    }
    codeWriter.appendLine(";");
  }
  codeWriter.appendLine("}" + structStatement->name.lexeme + ";");
  // TODO: Generate Struct new function
  // TODO: Generate Struct Free Function
}

void CodeGenerator::visit(BlockStatement *blockStatement) {
  codeWriter.appendLine("{");
  for (auto statement : blockStatement->statements) {
    statement->accept(this);
  }
  codeWriter.appendLine("}");
}

void CodeGenerator::visit(FunctionStatement *funStatement) {
  codeWriter.append(funStatement->returnType.lexeme + " " +
                    funStatement->name.lexeme + " (");
  int paramSize = funStatement->parameters.size();
  int paramCounter = 0;
  for (auto param : funStatement->parameters) {
    paramCounter++;
    codeWriter.append(param.type.lexeme + " ");
    MemoryType memoryType = param.memoryType;
    generateMemoryType(memoryType);
    codeWriter.append(param.name.lexeme);
    if (param.isArrayType) {
      codeWriter.append("[]");
    }
    if (paramSize != paramCounter) {
      codeWriter.append(", ");
    }
  }

  codeWriter.appendLine(") {");

  for (auto statement : funStatement->body) {
    statement->accept(this);
  }

  codeWriter.appendLine("}");
}

void CodeGenerator::visit(LineFunctionStatement *funStatement) {
  codeWriter.append(funStatement->returnType.lexeme + " " +
                    funStatement->name.lexeme + " (");
  int paramSize = funStatement->parameters.size();
  int paramCounter = 0;
  for (auto param : funStatement->parameters) {
    paramCounter++;
    codeWriter.append(param.type.lexeme + " ");
    MemoryType memoryType = param.memoryType;
    generateMemoryType(memoryType);
    codeWriter.append(param.name.lexeme);
    if (param.isArrayType) {
      codeWriter.append("[]");
    }
    if (paramSize != paramCounter) {
      codeWriter.append(", ");
    }
  }

  codeWriter.appendLine(") {");
  funStatement->body->accept(this);
  codeWriter.appendLine("}");
}

void CodeGenerator::visit(IfStatement *ifStatement) {
  codeWriter.append("if(");
  ifStatement->condition->accept(this);
  codeWriter.appendLine("){");
  for (auto statement : ifStatement->body) {
    statement->accept(this);
  }
  codeWriter.appendLine("}");

  for (auto statement : ifStatement->elseIfStatements) {
    statement->accept(this);
  }

  if (ifStatement->elseStatement != nullptr) {
    ifStatement->elseStatement->accept(this);
  }
}

void CodeGenerator::visit(ElseIfStatement *elseIfStatement) {
  codeWriter.append("else if(");
  elseIfStatement->condition->accept(this);
  codeWriter.appendLine("){");
  for (auto statement : elseIfStatement->body) {
    statement->accept(this);
  }
  codeWriter.appendLine("}");
}

void CodeGenerator::visit(ElseStatement *elseStatement) {
  codeWriter.appendLine("else{");
  for (auto statement : elseStatement->body) {
    statement->accept(this);
  }
  codeWriter.appendLine("}");
}

void CodeGenerator::visit(WhileStatement *whileStatement) {
  codeWriter.append("while(");
  whileStatement->condition->accept(this);
  codeWriter.appendLine("){");
  for (auto statement : whileStatement->body) {
    statement->accept(this);
  }
  codeWriter.appendLine("}");
}

void CodeGenerator::visit(DoWhileStatement *doWhileStatement) {
  codeWriter.appendLine("do (");
  for (auto statement : doWhileStatement->body) {
    statement->accept(this);
  }
  codeWriter.append("}");
  codeWriter.append("while(");
  doWhileStatement->condition->accept(this);
  codeWriter.appendLine(");");
}

void CodeGenerator::visit(ArrayStatement *arrayStatement) {
  codeWriter.append(arrayStatement->type.lexeme + " ");
  MemoryType type = arrayStatement->memoryType;
  generateMemoryType(type);
  codeWriter.append(arrayStatement->name.lexeme);
  codeWriter.append("[");
  if (arrayStatement->size != nullptr) {
    arrayStatement->size->accept(this);
  }
  codeWriter.append("]");
  if (arrayStatement->isInitialized) {
    codeWriter.append("=");
    arrayStatement->value->accept(this);
  }
  codeWriter.appendLine(";");
}

void CodeGenerator::visit(ReturnStatement *returnStatement) {
  codeWriter.append("return ");
  if (returnStatement->expression != nullptr) {
    returnStatement->expression->accept(this);
  }
  codeWriter.appendLine(";");
}

void CodeGenerator::visit(AssignExpression *assign) {
  generateMemoryType(assign->type);
  assign->name->accept(this);
  codeWriter.append("=");
  assign->value->accept(this);
  codeWriter.appendLine(";");
}

void CodeGenerator::visit(ExpressionStatement *expressionStatement) {
  expressionStatement->expression->accept(this);
  codeWriter.appendLine(";");
}

void CodeGenerator::visit(LiteralExpression *literal) {
  codeWriter.append(literal->value);
}

void CodeGenerator::visit(CallExpression *callExpression) {
  callExpression->callee->accept(this);
  codeWriter.append("(");
  int argsSize = callExpression->arguments.size();
  int argsCounter = 1;
  for (auto arg : callExpression->arguments) {
    arg->accept(this);
    if (argsCounter != argsSize) {
      codeWriter.append(",");
    }
    argsCounter++;
  }
  codeWriter.append(")");
}

void CodeGenerator::visit(VariableExpression *varExpression) {
  MemoryType memoryType = varExpression->memoryType;
  generateMemoryType(memoryType);
  codeWriter.append(varExpression->name.lexeme);
}

void CodeGenerator::visit(GroupExpression *groupExpression) {
  codeWriter.append("(");
  groupExpression->expression->accept(this);
  codeWriter.append(")");
}

void CodeGenerator::visit(LogicalExpression *groupExpression) {
  groupExpression->left->accept(this);
  Token opt = groupExpression->opt;
  switch (opt.tokenType) {
  case OR: {
    codeWriter.append("||");
    break;
  }
  case XOR: {
    codeWriter.append("^");
    break;
  }
  case AND: {
    codeWriter.append("&&");
    break;
  }
  }
  groupExpression->right->accept(this);
}

void CodeGenerator::visit(GetExpression *getExpression) {
  getExpression->object->accept(this);
  codeWriter.append("." + getExpression->name.lexeme);
}

void CodeGenerator::visit(TernaryExpression *ternaryExpression) {
  ternaryExpression->condition->accept(this);
  codeWriter.append("?");
  ternaryExpression->truthExpr->accept(this);
  codeWriter.append(":");
  ternaryExpression->falseExpr->accept(this);
}

void CodeGenerator::visit(BinaryExpression *binaryExpression) {
  TokenType optType = binaryExpression->opt.tokenType;
  binaryExpression->left->accept(this);
  switch (optType) {
  case EQUAL_EQUAL: {
    codeWriter.append("==");
    break;
  }
  case BANG_EQUAL: {
    codeWriter.append("!=");
    break;
  }
  case GREATER: {
    codeWriter.append(">");
    break;
  }
  case GREATER_EQUAL: {
    codeWriter.append(">=");
    break;
  }
  case LESS: {
    codeWriter.append("<");
    break;
  }
  case LESS_EQUAL: {
    codeWriter.append("<=");
    break;
  }
  case PLUS: {
    codeWriter.append("+");
    break;
  }
  case MINUS: {
    codeWriter.append("-");
    break;
  }
  case STAR: {
    codeWriter.append("*");
    break;
  }
  case SLASH: {
    codeWriter.append("/");
    break;
  }
  case PERCENT: {
    codeWriter.append("%");
    break;
  }
  }
  binaryExpression->right->accept(this);
}

void CodeGenerator::visit(UnaryExpression *unaryExpression) {
  TokenType optType = unaryExpression->opt.tokenType;
  switch (optType) {
  case BANG: {
    codeWriter.append("!");
    break;
  }
  case MINUS: {
    codeWriter.append("-");
    break;
  }
  case PLUS_PLUS: {
    codeWriter.append("++");
    break;
  }
  case MINUS_MINUS: {
    codeWriter.append("--");
    break;
  }
  }
  unaryExpression->expression->accept(this);
}

void CodeGenerator::visit(ArrayExpression *arrayExpression) {
  arrayExpression->variable->accept(this);
  codeWriter.append("[");
  arrayExpression->index->accept(this);
  codeWriter.append("]");
}

void CodeGenerator::visit(ArrayValuesExpression *arrayExpression) {
  codeWriter.append("{");
  int valuesSize = arrayExpression->values.size();
  int valuesCounter = 1;
  for (auto val : arrayExpression->values) {
    val->accept(this);
    if (valuesCounter != valuesSize) {
      codeWriter.append(",");
    }
    valuesCounter++;
  }
  codeWriter.append("}");
}

void CodeGenerator::generateMemoryType(MemoryType type) {
  if (type == SINGLE_POINTER) {
    codeWriter.append("*");
  } else if (type == DOUBLE_POINTER) {
    codeWriter.append("**");
  } else if (type == ADDRESS_POINTER) {
    codeWriter.append("&");
  }
}
