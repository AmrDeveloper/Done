
#ifndef DONELANG_BLOCKSTATEMENT_H
#define DONELANG_BLOCKSTATEMENT_H

#include "Statement.h"

#include <utility>
#include <vector>

class BlockStatement : public Statement{
public:
    std::vector<Statement*> statements;
    BlockStatement(std::vector<Statement*> statements) : statements(std::move(statements)){}
    void accept(StatementVisitor *visitor) {
        visitor->visit(this);
    }
};

#endif
