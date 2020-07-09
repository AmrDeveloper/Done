
#ifndef DONELANG_ELSESTATEMENT_H
#define DONELANG_ELSESTATEMENT_H

#include "Statement.h"
#include <utility>
#include <vector>

class ElseStatement : public Statement {
public:
    std::vector<Statement*> body;
    ElseStatement(std::vector<Statement*> body) : body(std::move(body)) {}
    void accept(StatementVisitor *visitor) {
        visitor->visit(this);
    }
};

#endif
