
#ifndef DONELANG_EXPRESSION_H
#define DONELANG_EXPRESSION_H

#include "ExpressionVisitor.h"

class Expression {

public:
    virtual void accept(class ExpressionVisitor* visitor) {
        std::cout<<"Hello from Expression";
    }
};

#endif
