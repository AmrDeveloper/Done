//
// Created by AmrDeveloper on 7/7/2020.
//

#ifndef DONELANG_RETURNSTATEMENT_H
#define DONELANG_RETURNSTATEMENT_H

#include "Expression.h"
#include "Statement.h"

class ReturnStatement : public Statement{
public:
    Expression* expression;
    ReturnStatement(Expression* value) : expression(value) {}
    void accept(class StatementVisitor *visitor) {
        visitor->visit(this);
    }
};

#endif //DONELANG_RETURNSTATEMENT_H
