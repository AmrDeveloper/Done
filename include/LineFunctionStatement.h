
#ifndef DONELANG_LINEFUNCTIONSTATEMENT_H
#define DONELANG_LINEFUNCTIONSTATEMENT_H

#include <utility>
#include <vector>

#include "Token.h"
#include "Statement.h"
#include "Expression.h"
#include "Parameter.h"

class LineFunctionStatement : public Statement {
public:
    Token name;
    Token returnType;
    std::vector<Parameter> parameters;
    Statement* body;
    LineFunctionStatement(Token n, Token t, std::vector<Parameter> params, Statement* body) :
            name(std::move(n)), returnType(std::move(t)),
            parameters(std::move(params)), body(body) {}
    void accept(StatementVisitor *visitor) {
        visitor->visit(this);
    }
};

#endif //DONELANG_LINEFUNCTIONSTATEMENT_H
