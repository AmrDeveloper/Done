//
// Created by AmrDeveloper on 7/5/2020.
//

#ifndef DONELANG_WHILESTATEMENT_H
#define DONELANG_WHILESTATEMENT_H

#include "Expression.h"
#include "Statement.h"

#include <utility>
#include <vector>

class WhileStatement  : public Statement {
public:
    Expression* condition;
    std::vector<Statement *> body;
    WhileStatement(Expression* c,
             std::vector<Statement *> b) : condition(c) , body(std::move(b)){}
    void accept(class StatementVisitor *visitor) {
        visitor->visit(this);
    }
};

#endif //DONELANG_WHILESTATEMENT_H
