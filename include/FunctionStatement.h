
#ifndef DONELANG_FUNCTIONSTATEMENT_H
#define DONELANG_FUNCTIONSTATEMENT_H

#include <utility>
#include <vector>

#include "Token.h"
#include "Statement.h"
#include "Expression.h"
#include "Parameter.h"

class FunctionStatement : public Statement {
public:
    Token name;
    Token returnType;
    std::vector<Parameter> parameters;
    std::vector<Statement*> body;
    Expression* returnValue;
    FunctionStatement(Token n, Token t, std::vector<Parameter> params, std::vector<Statement*> body, Expression* returnValue) :
                        name(std::move(n)), returnType(std::move(t)),
                        parameters(std::move(params)), body(std::move(body)), returnValue(returnValue){}
    void accept(StatementVisitor *visitor) {
        visitor->visit(this);
    }
};
#endif
