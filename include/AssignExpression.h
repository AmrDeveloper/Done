
#ifndef DONELANG_ASSIGNEXPRESSION_H
#define DONELANG_ASSIGNEXPRESSION_H

#include "Token.h"
#include "Expression.h"

class AssignExpression : public Expression{
public:
    Expression* name;
    Expression* value;
    MemoryType type;
    AssignExpression(Expression* name, Expression* val, MemoryType type)
                   : name(name), value(val), type(type){}
    void accept(ExpressionVisitor *visitor) {
        visitor->visit(this);
    }
};

#endif
