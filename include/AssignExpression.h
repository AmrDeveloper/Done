
#ifndef DONELANG_ASSIGNEXPRESSION_H
#define DONELANG_ASSIGNEXPRESSION_H

#include "Token.h"
#include "Expression.h"

class AssignExpression : public Expression{
public:
    Token name;
    Expression* value;
    AssignExpression(Token token, Expression* val) : name(std::move(token)), value(val){}
    void accept(ExpressionVisitor *visitor) {
        visitor->visit(this);
    }
};

#endif
