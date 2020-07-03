//
// Created by AmrDeveloper on 7/1/2020.
//

#ifndef DONELANG_VARSTATEMENT_H
#define DONELANG_VARSTATEMENT_H

#include "Statement.h"
#include "Expression.h"

#include <utility>
#include "Token.h"

class VarStatement;

class VarStatement : public Statement {
public:
    Token name;
    Token type;
    bool isPointer;
    bool isInitialized;
    Expression* value;

    VarStatement(Token n, Token t, bool pointer, bool isInit, Expression* val)
    : name(std::move(n)), type(std::move(t)), isPointer(pointer) ,isInitialized(isInit), value(val) {}

    void accept(StatementVisitor *visitor) {
        visitor->visit(this);
    }
};

#endif
