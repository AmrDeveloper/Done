#ifndef DONELANG_STATEMENTVISITOR_H
#define DONELANG_STATEMENTVISITOR_H

class EnumStatement;
class VarStatement;
class StructStatement;
class ExpressionStatement;
class BlockStatement;
class FunctionStatement;
class IfStatement;
class WhileStatement;
class ArrayStatement;

class StatementVisitor{
public:
    virtual void visit(EnumStatement *statement) {};

    virtual void visit(VarStatement *statement) {};

    virtual void visit(StructStatement *statement) {};

    virtual void visit(BlockStatement *statement) {};

    virtual void visit(FunctionStatement *statement) {};

    virtual void visit(ExpressionStatement *statement) {};

    virtual void visit(IfStatement *statement) {};

    virtual void visit(WhileStatement *statement) {};

    virtual void visit(ArrayStatement *statement) {};
};

#endif
