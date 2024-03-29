
#ifndef DONELANG_CODEGENERATOR_H
#define DONELANG_CODEGENERATOR_H

#include <memory>
#include <set>
#include <vector>

#include "CompilerContext.h"

#include "Expressions.h"
#include "Statements.h"

#include "CodeWriter.h"
#include "ErrorHandler.h"

class CodeGenerator : public StatementVisitor, ExpressionVisitor {
public:
  explicit CodeGenerator(CompilerContext *context);

  std::string generateCode(const std::vector<Statement *> &statements);

  void generateSourceCodeHeaders(const std::set<std::string> &libs);

  void visit(EnumStatement *enumStatement) override;

  void visit(VarStatement *varStatement) override;

  void visit(StructStatement *structStatement) override;

  void visit(ExpressionStatement *expressionStatement) override;

  void visit(BlockStatement *blockStatement) override;

  void visit(FunctionStatement *funStatement) override;

  void visit(LineFunctionStatement *funStatement) override;

  void visit(IfStatement *ifStatement) override;

  void visit(ElseIfStatement *ifStatement) override;

  void visit(ElseStatement *ifStatement) override;

  void visit(WhileStatement *whileStatement) override;

  void visit(DoWhileStatement *dowhileStatement) override;

  void visit(ArrayStatement *arrayStatement) override;

  void visit(ReturnStatement *returnStatement) override;

  void visit(AssignExpression *assignExpression) override;

  void visit(LiteralExpression *literalExpression) override;

  void visit(CallExpression *callExpression) override;

  void visit(VariableExpression *varExpression) override;

  void visit(GroupExpression *groupExpression) override;

  void visit(LogicalExpression *logicalExpression) override;

  void visit(GetExpression *getExpression) override;

  void visit(TernaryExpression *ternaryExpression) override;

  void visit(BinaryExpression *binaryExpression) override;

  void visit(UnaryExpression *unaryExpression) override;

  void visit(ArrayExpression *arrayExpression) override;

  void visit(ArrayValuesExpression *arrayExpression) override;

  void generateMemoryType(MemoryType type);

private:
  CodeWriter codeWriter;
  CompilerContext *context;
};

#endif
