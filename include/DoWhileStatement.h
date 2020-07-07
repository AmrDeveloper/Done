//
// Created by AmrDeveloper on 7/7/2020.
//

#ifndef DONELANG_DOWHILESTATEMENT_H
#define DONELANG_DOWHILESTATEMENT_H

#include "Expression.h"
#include "Statement.h"

#include <utility>
#include <vector>

class DoWhileStatement  : public Statement {
public:
    Expression* condition;
    std::vector<Statement *> body;
    DoWhileStatement(Expression* c,
                   std::vector<Statement *> b) : condition(c) , body(std::move(b)){}
    void accept(class StatementVisitor *visitor) {
        visitor->visit(this);
    }
};

#endif //DONELANG_DOWHILESTATEMENT_H
