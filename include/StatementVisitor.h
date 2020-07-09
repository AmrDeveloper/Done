#ifndef DONELANG_STATEMENTVISITOR_H
#define DONELANG_STATEMENTVISITOR_H

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

#endif
