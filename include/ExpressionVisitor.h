
#ifndef DONELANG_EXPRESSIONVISITOR_H
#define DONELANG_EXPRESSIONVISITOR_H

class AssignExpression;
class LiteralExpression;
class CallExpression;
class VariableExpression;
class GroupExpression;

class ExpressionVisitor {
public:
    virtual void visit(AssignExpression * assign) {};
    virtual void visit(LiteralExpression * literal) {};
    virtual void visit(CallExpression * call) {};
    virtual void visit(VariableExpression * var) {};
    virtual void visit(GroupExpression * group) {};
};

#endif
