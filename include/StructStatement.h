
#ifndef DONELANG_STRUCTSTATEMENT_H
#define DONELANG_STRUCTSTATEMENT_H

#include "Token.h"
#include "VarStatement.h"
#include <utility>
#include <vector>

class StructStatement;

class StructStatement : public Statement{
public:
    Token name;
    std::vector<Statement*> fields;
    StructStatement(Token n, std::vector<Statement*> f)
    : name(std::move(n)), fields(std::move(f)){}
    void accept(StatementVisitor *visitor) {
        visitor->visit(this);
    }
};
#endif
