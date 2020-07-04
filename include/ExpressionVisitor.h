
#ifndef DONELANG_EXPRESSIONVISITOR_H
#define DONELANG_EXPRESSIONVISITOR_H

class AssignExpression;
class LiteralExpression;
class CallExpression;
class VariableExpression;

class ExpressionVisitor {
public:
    virtual void visit(AssignExpression * assign) {};
    virtual void visit(LiteralExpression * literal) {};
    virtual void visit(CallExpression * call) {};
    virtual void visit(VariableExpression * var) {};
};

#endif
