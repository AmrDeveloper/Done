
#ifndef DONELANG_IFSTATEMENT_H
#define DONELANG_IFSTATEMENT_H

#include "Expression.h"
#include "Statement.h"
#include "ElseIfStatement.h"
#include "ElseStatement.h"
#include <utility>
#include <vector>

class IfStatement : public Statement {
public:
    Expression* condition;
    std::vector<Statement*> body;
    std::vector<ElseIfStatement *> elseIfStatements;
    Statement* elseStatement;
    IfStatement(Expression* condition,
            std::vector<Statement*> body,
            std::vector<ElseIfStatement *> elseIfStatements,
            Statement* elseStatement)
                               :condition(condition),
                               body(std::move(body)),
                               elseIfStatements(std::move(elseIfStatements)),
                               elseStatement(elseStatement)
                               {}
    void accept(StatementVisitor *visitor) {
        visitor->visit(this);
    }
};
#endif
