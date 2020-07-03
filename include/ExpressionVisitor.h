
#ifndef DONELANG_EXPRESSIONVISITOR_H
#define DONELANG_EXPRESSIONVISITOR_H

class AssignExpression;
class LiteralExpression;

class ExpressionVisitor {
public:
    virtual void visit(AssignExpression * assign) {};
    virtual void visit(LiteralExpression * literal) {};
};

#endif
