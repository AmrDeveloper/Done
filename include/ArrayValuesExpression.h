
#ifndef DONELANG_ARRAYVALUESEXPRESSION_H
#define DONELANG_ARRAYVALUESEXPRESSION_H

#include <utility>
#include <vector>
#include "Expression.h"

class ArrayValuesExpression : public Expression {
public:
    std::vector<Expression *> values;
    ArrayValuesExpression(std::vector<Expression *> vals)
            : values(std::move(vals)) {}
    void accept(class ExpressionVisitor *visitor) {
        visitor->visit(this);
    }
};
#endif
