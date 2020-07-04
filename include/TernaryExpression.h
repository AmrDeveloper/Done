//
// Created by AmrDeveloper on 7/4/2020.
//

#ifndef DONELANG_TERNARYEXPRESSION_H
#define DONELANG_TERNARYEXPRESSION_H

#include "Expression.h"

class TernaryExpression : public Expression {
public:
    Expression* condition;
    Expression* truthExpr;
    Expression* falseExpr;
    TernaryExpression(Expression* c, Expression* t, Expression* f) :
             condition(c), truthExpr(t), falseExpr(f){}
    void accept(class ExpressionVisitor *visitor) {
        visitor->visit(this);
    }
};

#endif //DONELANG_TERNARYEXPRESSION_H
