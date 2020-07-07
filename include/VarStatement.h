//
// Created by AmrDeveloper on 7/1/2020.
//

#ifndef DONELANG_VARSTATEMENT_H
#define DONELANG_VARSTATEMENT_H

#include "Statement.h"
#include "Expression.h"

#include <utility>
#include "Token.h"


class VarStatement : public Statement {
public:
    Token name;
    Token type;
    MemoryType memoryType;
    bool isConst;
    bool isInitialized;
    Expression* value;

    VarStatement(Token n, Token t, MemoryType type, bool isInit, Expression* val, bool isConst)
    : name(std::move(n)), type(std::move(t)), memoryType(type)
    ,isInitialized(isInit), value(val), isConst(isConst) {}

    void accept(StatementVisitor *visitor) {
        visitor->visit(this);
    }
};

#endif
