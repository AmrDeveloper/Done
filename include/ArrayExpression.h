
#ifndef DONELANG_ARRAYEXPRESSION_H
#define DONELANG_ARRAYEXPRESSION_H

#include "Expression.h"
#include "VariableExpression.h"

class ArrayExpression : public Expression{
public:
    VariableExpression* variable;
    Expression* index;
    ArrayExpression(VariableExpression* var, Expression* i)
          : variable(var), index(i){}
    void accept(class ExpressionVisitor *visitor) {
        visitor->visit(this);
    }
};

#endif
