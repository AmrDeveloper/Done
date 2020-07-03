//
// Created by AmrDeveloper on 7/3/2020.
//

#ifndef DONELANG_LITERALEXPRESSION_H
#define DONELANG_LITERALEXPRESSION_H

#include <string>
#include <utility>
#include "Expression.h"

class LiteralExpression : public Expression{
public:
    std::string value;
    LiteralExpression(std::string val) : value(std::move(val)){}
    void accept(ExpressionVisitor *visitor) {
        visitor->visit(this);
    }
};

#endif
