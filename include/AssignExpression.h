
#ifndef DONELANG_ASSIGNEXPRESSION_H
#define DONELANG_ASSIGNEXPRESSION_H

#include "Token.h"
#include "Expression.h"

class AssignExpression : public Expression{
public:
    Token name;
    Expression* value;
    bool isPointer;
    AssignExpression(Token token, Expression* val, bool pointer)
                   : name(std::move(token)), value(val), isPointer(pointer){}
    void accept(ExpressionVisitor *visitor) {
        visitor->visit(this);
    }
};

#endif
