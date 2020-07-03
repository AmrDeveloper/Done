
#ifndef DONELANG_CODEGENERATOR_H
#define DONELANG_CODEGENERATOR_H

#include <vector>
#include <memory>

#include "Statement.h"
#include "EnumStatement.h"
#include "VarStatement.h"
#include "StatementVisitor.h"
#include "ExpressionVisitor.h"
#include "LiteralExpression.h"
#include "StructStatement.h"
#include "ExpressionStatement.h"
#include "BlockStatement.h"
#include "FunctionStatement.h"
#include "IfStatement.h"

#include "ErrorHandler.h"
#include "CodeWriter.h"

class CodeGenerator : public StatementVisitor, ExpressionVisitor {
public:
    explicit CodeGenerator(ErrorHandler &errorHandler);

    void generateCode(const std::vector<Statement *> &statements);

    void visit(EnumStatement *enumStatement) override;

    void visit(VarStatement *varStatement) override;

    void visit(StructStatement *structStatement) override;

    void visit(ExpressionStatement *expressionStatement) override;

    void visit(BlockStatement *blockStatement) override;

    void visit(FunctionStatement *blockStatement) override;

    void visit(IfStatement *blockStatement) override;

    void visit(AssignExpression *enumStatement) override;

    void visit(LiteralExpression *enumStatement) override;

private:
    ErrorHandler &errorHandler;
};

#endif
