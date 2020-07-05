//
// Created by AmrDeveloper on 7/5/2020.
//

#ifndef DONELANG_BINARYEXPRESSION_H
#define DONELANG_BINARYEXPRESSION_H

#include "Expression.h"
#include "Token.h"

class BinaryExpression : public Expression{
public:
    Expression* right;
    Expression* left;
    Token opt;
    BinaryExpression(Expression* r, Expression* l, Token o)
    : right(r), left(l), opt(std::move(o)){}
    void accept(class ExpressionVisitor *visitor) {
        visitor->visit(this);
    }
};

#endif //DONELANG_BINARYEXPRESSION_H
