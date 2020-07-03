
#ifndef DONELANG_EXPRESSIONSTATEMENT_H
#define DONELANG_EXPRESSIONSTATEMENT_H

#include "Expression.h"
#include "Statement.h"

class ExpressionStatement : public Statement{
public:
    Expression* expression;
    ExpressionStatement(Expression* exp) : expression(exp) {}
    void accept(StatementVisitor *visitor) {
        visitor->visit(this);
    }
};
#endif
