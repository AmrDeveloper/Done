
#ifndef DONELANG_ELSEIFSTATEMENT_H
#define DONELANG_ELSEIFSTATEMENT_H

#include "Expression.h"
#include "Statement.h"
#include <utility>
#include <vector>

class ElseIfStatement : public Statement {
public:
    Expression* condition;
    std::vector<Statement*> body;
    ElseIfStatement(Expression* condition, std::vector<Statement*> body)
            :condition(condition), body(std::move(body)) {}
    void accept(StatementVisitor *visitor) {
        visitor->visit(this);
    }
};

#endif
