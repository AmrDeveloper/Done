
#ifndef DONELANG_LOGICALEXPRESSION_H
#define DONELANG_LOGICALEXPRESSION_H

#include "Expression.h"

#include <utility>
#include "Token.h"

class LogicalExpression : public Expression{
public:
    Expression* right;
    Expression* left;
    Token opt;
    LogicalExpression(Expression* r, Expression* l, Token o)
            : right(r), left(l), opt(std::move(o)){}
    void accept(class ExpressionVisitor *visitor) {
        visitor->visit(this);
    }
};

#endif
