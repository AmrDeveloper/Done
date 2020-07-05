
#ifndef DONELANG_UNARYEXPRESSION_H
#define DONELANG_UNARYEXPRESSION_H

#include <utility>

#include "Token.h"
#include "Expression.h"

class UnaryExpression : public Expression{
public:
    Token opt;
    Expression* expression;
    UnaryExpression(Token t, Expression* e)
            : opt(std::move(t)), expression(e) {}
    void accept(class ExpressionVisitor *visitor)  {
        visitor->visit(this);
    }
};

#endif
