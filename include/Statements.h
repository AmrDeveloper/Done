#ifndef DONELANG_STATEMENTS_H
#define DONELANG_STATEMENTS_H

#include <utility>
#include <vector>

#include "Token.h"
#include "Parameter.h"
#include "Expressions.h"

class EnumStatement;
class VarStatement;
class StructStatement;
class ExpressionStatement;
class BlockStatement;
class FunctionStatement;
class LineFunctionStatement;
class IfStatement;
class ElseIfStatement;
class ElseStatement;
class WhileStatement;
class DoWhileStatement;
class ArrayStatement;
class ReturnStatement;

class StatementVisitor{
public:
    virtual void visit(EnumStatement *statement) {};

    virtual void visit(VarStatement *statement) {};

    virtual void visit(StructStatement *statement) {};

    virtual void visit(BlockStatement *statement) {};

    virtual void visit(FunctionStatement *statement) {};

    virtual void visit(LineFunctionStatement *statement) {};

    virtual void visit(ExpressionStatement *statement) {};

    virtual void visit(IfStatement *statement) {};

    virtual void visit(ElseIfStatement *statement) {};

    virtual void visit(ElseStatement *statement) {};

    virtual void visit(WhileStatement *statement) {};

    virtual void visit(DoWhileStatement *statement) {};

    virtual void visit(ArrayStatement *statement) {};

    virtual void visit(ReturnStatement *statement) {};
};


class Statement {
public:
    virtual void accept(class StatementVisitor* visitor) {}
};


class StructStatement : public Statement {
public:
    Token name;
    std::vector<Parameter> fields;
    StructStatement(Token n, std::vector<Parameter> f): name(std::move(n)), fields(std::move(f)){}
    void accept(StatementVisitor *visitor) {
        visitor->visit(this);
    }
};

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


class VarStatement : public Statement {
public:
    Token name;
    Token type;
    MemoryType memoryType;
    bool isConst;
    bool isInitialized;
    Expression* value;

    VarStatement(Token n, Token t, MemoryType type, bool isInit, Expression* val, bool isConst)
    : name(std::move(n)), type(std::move(t)), memoryType(type)
    ,isInitialized(isInit), value(val), isConst(isConst) {}

    void accept(StatementVisitor *visitor) {
        visitor->visit(this);
    }
};


class BlockStatement : public Statement{
public:
    std::vector<Statement*> statements;
    BlockStatement(std::vector<Statement*> statements) : statements(std::move(statements)){}
    void accept(StatementVisitor *visitor) {
        visitor->visit(this);
    }
};


class FunctionStatement : public Statement {
public:
    Token name;
    Token returnType;
    std::vector<Parameter> parameters;
    std::vector<Statement*> body;
    FunctionStatement(Token n, Token t, std::vector<Parameter> params, std::vector<Statement*> body) :
                        name(std::move(n)), returnType(std::move(t)),
                        parameters(std::move(params)), body(std::move(body)){}
    void accept(StatementVisitor *visitor) {
        visitor->visit(this);
    }
};

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


class ExpressionStatement : public Statement{
public:
    Expression* expression;
    ExpressionStatement(Expression* exp) : expression(exp) {}
    void accept(StatementVisitor *visitor) {
        visitor->visit(this);
    }
};

class IfStatement : public Statement {
public:
    Expression* condition;
    std::vector<Statement*> body;
    std::vector<ElseIfStatement *> elseIfStatements;
    Statement* elseStatement;
    IfStatement(Expression* condition,
            std::vector<Statement*> body,
            std::vector<ElseIfStatement *> elseIfStatements,
            Statement* elseStatement)
                               :condition(condition),
                               body(std::move(body)),
                               elseIfStatements(std::move(elseIfStatements)),
                               elseStatement(elseStatement)
                               {}
    void accept(StatementVisitor *visitor) {
        visitor->visit(this);
    }
};

class ElseIfStatement : public Statement {
public:
    Expression* condition;
    std::vector<Statement*> body;
    ElseIfStatement(Expression* condition, std::vector<Statement*> body)
            :condition(condition), body(std::move(body)) {}
    void accept(StatementVisitor *visitor) {
        visitor->visit(this);
    }
};

class ElseStatement : public Statement {
public:
    std::vector<Statement*> body;
    ElseStatement(std::vector<Statement*> body) : body(std::move(body)) {}
    void accept(StatementVisitor *visitor) {
        visitor->visit(this);
    }
};


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


class ArrayStatement : public Statement {
public:
    Token name;
    Token type;
    Expression *size;
    MemoryType memoryType;
    bool isInitialized;
    Expression *value;

    ArrayStatement(Token n, Token t, Expression *size, MemoryType type, bool isInit, Expression *val)
            : name(std::move(n)), type(std::move(t)), size(size), memoryType(type) ,isInitialized(isInit), value(val){}

    void accept(StatementVisitor *visitor) {
        visitor->visit(this);
    }
};


class ReturnStatement : public Statement{
public:
    Expression* expression;
    ReturnStatement(Expression* value) : expression(value) {}
    void accept(class StatementVisitor *visitor) {
        visitor->visit(this);
    }
};

#endif