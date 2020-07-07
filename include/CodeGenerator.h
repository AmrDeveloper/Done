
#ifndef DONELANG_CODEGENERATOR_H
#define DONELANG_CODEGENERATOR_H

#include <vector>
#include <memory>
#include <set>

#include "Statement.h"
#include "EnumStatement.h"
#include "VarStatement.h"
#include "StatementVisitor.h"
#include "ExpressionVisitor.h"

#include "StructStatement.h"
#include "ExpressionStatement.h"
#include "BlockStatement.h"
#include "FunctionStatement.h"
#include "LineFunctionStatement.h"
#include "IfStatement.h"
#include "WhileStatement.h"
#include "DoWhileStatement.h"
#include "ArrayStatement.h"

#include "LiteralExpression.h"
#include "AssignExpression.h"
#include "CallExpression.h"
#include "VariableExpression.h"
#include "GroupExpression.h"
#include "LogicalExpression.h"
#include "GetExpression.h"
#include "TernaryExpression.h"
#include "BinaryExpression.h"
#include "UnaryExpression.h"
#include "ArrayExpression.h"
#include "ArrayValuesExpression.h"

#include "ErrorHandler.h"
#include "CodeWriter.h"

class CodeGenerator : public StatementVisitor, ExpressionVisitor {
public:
    CodeWriter codeWriter;

    explicit CodeGenerator(ErrorHandler &errorHandler);

    void generateCode(const std::vector<Statement *> &statements);

    void generateCode(const std::vector<Statement *> &statements, const std::set<std::string>& libs);

    void visit(const std::set<std::string>& libs);

    void visit(EnumStatement *enumStatement) override;

    void visit(VarStatement *varStatement) override;

    void visit(StructStatement *structStatement) override;

    void visit(ExpressionStatement *expressionStatement) override;

    void visit(BlockStatement *blockStatement) override;

    void visit(FunctionStatement *funStatement) override;

    void visit(LineFunctionStatement *funStatement) override;

    void visit(IfStatement *ifStatement) override;

    void visit(WhileStatement *whileStatement) override;

    void visit(DoWhileStatement *dowhileStatement) override;

    void visit(ArrayStatement *arrayStatement) override;

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

    void visit(ArrayExpression* arrayExpression) override;

    void visit(ArrayValuesExpression* arrayExpression) override;

    void generateMemoryType(MemoryType type);
private:
    ErrorHandler &errorHandler;
};

#endif
