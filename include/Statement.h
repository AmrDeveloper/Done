#ifndef DONELANG_STATEMENT_H
#define DONELANG_STATEMENT_H

#include "StatementVisitor.h"
#include <iostream>

class Statement {
public:
    virtual void accept(class StatementVisitor* visitor) {
        std::cout<<"Hello from Statement";
    }
};

#endif
