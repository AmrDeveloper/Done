
#ifndef DONELANG_VARIABLEEXPRESSION_H
#define DONELANG_VARIABLEEXPRESSION_H

#include "Expression.h"

#include <utility>
#include "Token.h"

class VariableExpression : public Expression{
public:
    Token name;
    VariableExpression(Token name) : name(std::move(name)) {}
    void accept(ExpressionVisitor *visitor) {
        visitor->visit(this);
    }
};

#endif
