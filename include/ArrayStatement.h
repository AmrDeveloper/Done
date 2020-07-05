
#ifndef DONELANG_ARRAYSTATEMENT_H
#define DONELANG_ARRAYSTATEMENT_H

#include "Expression.h"
#include "Statement.h"

#include <utility>
#include "Token.h"

class ArrayStatement : public Statement {
public:
    Token name;
    Token type;
    Expression *size;
    MemoryType memoryType;
    bool isInitialized;
    Expression *value;

    ArrayStatement(Token n, Token t, Expression *size, MemoryType type, bool isInit, Expression *val)
            : name(std::move(n)), type(std::move(t)), size(size), memoryType(type) ,isInitialized(isInit), value(val){}

    void accept(StatementVisitor *visitor) {
        visitor->visit(this);
    }
};

#endif
