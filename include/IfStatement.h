
#ifndef DONELANG_IFSTATEMENT_H
#define DONELANG_IFSTATEMENT_H

#include "Expression.h"
#include "Statement.h"
#include <vector>

class IfStatement : public Statement {
public:
    Expression* condition;
    std::vector<Statement*> body;
    IfStatement(Expression* condition, std::vector<Statement*> body)
                               :condition(condition), body(body) {}
    void accept(StatementVisitor *visitor) {
        visitor->visit(this);
    }
};
#endif
