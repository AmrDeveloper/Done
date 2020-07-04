#ifndef DONELANG_GROUPEXPRESSION_H
#define DONELANG_GROUPEXPRESSION_H

#include "Expression.h"

class GroupExpression : public Expression{
public:
    Expression* expression;
    GroupExpression(Expression* expression)
            : expression(expression) {}
    void accept(class ExpressionVisitor *visitor)  {
        visitor->visit(this);
    }
};
#endif
