
#ifndef DONELANG_EXPRESSION_H
#define DONELANG_EXPRESSION_H

#include "ExpressionVisitor.h"
#include "MemoryType.h"

class Expression {

public:
    virtual void accept(class ExpressionVisitor* visitor) {}
};

#endif
