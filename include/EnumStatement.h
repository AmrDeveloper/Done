
#ifndef DONELANG_ENUMSTATEMENT_H
#define DONELANG_ENUMSTATEMENT_H

#include <vector>
#include "Token.h"
#include "Statement.h"

class EnumStatement;

class EnumStatement : public Statement {
public:
    Token name;
    std::vector<Token> fields;
    EnumStatement(Token token, std::vector<Token> fields)
            : name(std::move(token)), fields(std::move(fields)){}

    void accept(StatementVisitor *visitor) {
        visitor->visit(this);
    }
};

#endif
