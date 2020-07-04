#ifndef DONELANG_GETEXPRESSION_H
#define DONELANG_GETEXPRESSION_H

#include "Token.h"
#include "Expression.h"

#include <utility>

class GetExpression : public Expression{
public:
    Token name;
    Expression* object;
    GetExpression(Token n, Expression* o)
            : name(std::move(n)), object(o){}
    void accept(class ExpressionVisitor *visitor) {
         visitor->visit(this);
    }
};

#endif
