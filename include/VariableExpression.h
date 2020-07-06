
#ifndef DONELANG_VARIABLEEXPRESSION_H
#define DONELANG_VARIABLEEXPRESSION_H

#include "Expression.h"

#include <utility>
#include "Token.h"

class VariableExpression : public Expression{
public:
    Token name;
    MemoryType memoryType;
    VariableExpression(Token name, MemoryType memoryType) : name(std::move(name)), memoryType(memoryType) {}
    void accept(ExpressionVisitor *visitor) {
        visitor->visit(this);
    }
};

#endif
