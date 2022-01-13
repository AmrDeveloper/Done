#ifndef DONELANG_EXPRESSIONS_H
#define DONELANG_EXPRESSIONS_H

#include <string>
#include <utility>
#include <vector>

#include "MemoryType.h"
#include "Token.h"

class AssignExpression;
class LiteralExpression;
class CallExpression;
class VariableExpression;
class GroupExpression;
class LogicalExpression;
class GetExpression;
class TernaryExpression;
class BinaryExpression;
class UnaryExpression;
class ArrayExpression;
class ArrayValuesExpression;

class ExpressionVisitor {
public:
  virtual void visit(AssignExpression *assign){};
  virtual void visit(LiteralExpression *literal){};
  virtual void visit(CallExpression *call){};
  virtual void visit(VariableExpression *var){};
  virtual void visit(GroupExpression *group){};
  virtual void visit(LogicalExpression *logical){};
  virtual void visit(GetExpression *get){};
  virtual void visit(TernaryExpression *ternary){};
  virtual void visit(BinaryExpression *ternary){};
  virtual void visit(UnaryExpression *unary){};
  virtual void visit(ArrayExpression *array){};
  virtual void visit(ArrayValuesExpression *arrayVals){};
};

class Expression {

public:
  virtual void accept(class ExpressionVisitor *visitor) {}
};

class AssignExpression : public Expression {
public:
  Expression *name;
  Expression *value;
  MemoryType type;
  AssignExpression(Expression *name, Expression *val, MemoryType type)
      : name(name), value(val), type(type) {}
  void accept(ExpressionVisitor *visitor) { visitor->visit(this); }
};

class LiteralExpression : public Expression {
public:
  std::string value;
  LiteralExpression(std::string val) : value(std::move(val)) {}
  void accept(ExpressionVisitor *visitor) { visitor->visit(this); }
};

class CallExpression : public Expression {

public:
  Expression *callee;
  std::vector<Expression *> arguments;
  CallExpression(Expression *callee, std::vector<Expression *> arguments)
      : callee(callee), arguments(std::move(arguments)) {}
  void accept(ExpressionVisitor *visitor) { visitor->visit(this); }
};

class VariableExpression : public Expression {
public:
  Token name;
  MemoryType memoryType;
  VariableExpression(Token name, MemoryType memoryType)
      : name(std::move(name)), memoryType(memoryType) {}
  void accept(ExpressionVisitor *visitor) { visitor->visit(this); }
};

class GroupExpression : public Expression {
public:
  Expression *expression;
  GroupExpression(Expression *expression) : expression(expression) {}
  void accept(class ExpressionVisitor *visitor) { visitor->visit(this); }
};

class LogicalExpression : public Expression {
public:
  Expression *right;
  Expression *left;
  Token opt;
  LogicalExpression(Expression *r, Expression *l, Token o)
      : right(r), left(l), opt(std::move(o)) {}
  void accept(class ExpressionVisitor *visitor) { visitor->visit(this); }
};

class GetExpression : public Expression {
public:
  Token name;
  Expression *object;
  GetExpression(Token n, Expression *o) : name(std::move(n)), object(o) {}
  void accept(class ExpressionVisitor *visitor) { visitor->visit(this); }
};

class TernaryExpression : public Expression {
public:
  Expression *condition;
  Expression *truthExpr;
  Expression *falseExpr;
  TernaryExpression(Expression *c, Expression *t, Expression *f)
      : condition(c), truthExpr(t), falseExpr(f) {}
  void accept(class ExpressionVisitor *visitor) { visitor->visit(this); }
};

class BinaryExpression : public Expression {
public:
  Expression *right;
  Expression *left;
  Token opt;
  BinaryExpression(Expression *r, Expression *l, Token o)
      : right(r), left(l), opt(std::move(o)) {}
  void accept(class ExpressionVisitor *visitor) { visitor->visit(this); }
};

class UnaryExpression : public Expression {
public:
  Token opt;
  Expression *expression;
  UnaryExpression(Token t, Expression *e) : opt(std::move(t)), expression(e) {}
  void accept(class ExpressionVisitor *visitor) { visitor->visit(this); }
};

class ArrayExpression : public Expression {
public:
  VariableExpression *variable;
  Expression *index;
  ArrayExpression(VariableExpression *var, Expression *i)
      : variable(var), index(i) {}
  void accept(class ExpressionVisitor *visitor) { visitor->visit(this); }
};

class ArrayValuesExpression : public Expression {
public:
  std::vector<Expression *> values;
  ArrayValuesExpression(std::vector<Expression *> vals)
      : values(std::move(vals)) {}
  void accept(class ExpressionVisitor *visitor) { visitor->visit(this); }
};

#endif