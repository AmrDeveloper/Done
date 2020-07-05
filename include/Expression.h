
#ifndef DONELANG_EXPRESSION_H
#define DONELANG_EXPRESSION_H

#include "ExpressionVisitor.h"

enum MemoryType {
   SINGLE_POINTER,
   DOUBLE_POINTER,
   ADDRESS_POINTER,
   NONE
};

class Expression {

public:
    virtual void accept(class ExpressionVisitor* visitor) {
        std::cout<<"Hello from Expression";
    }
};

#endif
