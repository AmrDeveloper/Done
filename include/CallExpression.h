#ifndef DONELANG_CALLEXPRESSION_H
#define DONELANG_CALLEXPRESSION_H

#include <utility>
#include <vector>

#include "Expression.h"
#include "Statement.h"

class CallExpression : public Expression {

public:
    Expression* callee;
    std::vector<Expression* > arguments;
    CallExpression(Expression* callee, std::vector<Expression* > arguments)
                    : callee(callee), arguments(std::move(arguments)) {}
    void accept(ExpressionVisitor *visitor) {
        visitor->visit(this);
    }
};

#endif
