#pragma once
#include <iostream>
#include <vector>
class Identifier;

class Object
{
private:
    /* data */
public:
    Object(){};
    Object(std::string value){};
    ~Object(){};
};

class Node
{
private:
public:
    Node(){};
    ~Node(){};
};

class Expression : public Node
{
private:
    /* data */
public:
    Expression(){};
    ~Expression(){};
};

class Statement : public Node
{
private:
    /* data */
public:
    Statement(Expression &expr){};
    ~Statement(){};
};

class Block : public Node
{
private:
    std::vector<Statement *> statements;

public:
    Block(){};
    ~Block(){};
    void Append(Statement *state) { statements.push_back(state); };
};

class AssignExpression : public Expression
{
private:
public:
    AssignExpression(Identifier &ident, Expression &expression){};
    AssignExpression(Identifier &ident, Object &obj){};
    ~AssignExpression(){};
};

class BinaryExpression : public Expression
{
private:
    Expression expr1;
    Expression expr2;
    Object obj;
    int op;

public:
    BinaryExpression(Expression &expr1, int &op, Expression &expr2)
        : expr1(expr1), expr2(expr2), op(op){};
    BinaryExpression(Object &obj, int &op, Expression &expr)
        : expr1(expr), obj(obj), op(op){};
    BinaryExpression(Expression &expr, int &op, Object &obj)
        : expr1(expr), obj(obj), op(op){};
    ~BinaryExpression(){};
};

class ConstExpression : public Expression
{
private:
    Object obj;

public:
    ConstExpression(Object &objct) : obj(obj){};
    ~ConstExpression(){};
};

class CallExpression : public Expression
{
private:
    /* data */
public:
    CallExpression(){};
    ~CallExpression(){};
};

class FunctionExpression : public Expression
{
private:
    /* data */
public:
    FunctionExpression(){};
    ~FunctionExpression(){};
};

class Identifier : public Expression
{
private:
    /* data */
public:
    Identifier(){};
    ~Identifier(){};
    Object *get_value() { return nullptr; };
};

class IfExpression : public Expression
{
private:
    Expression expr;
    Block block1;
    Block block2;

public:
    IfExpression(Expression &expr, Block &block) : expr(expr), block1(block){};
    IfExpression(Expression &expr, Block &block1, Block &block2) : expr(expr), block1(block1), block2(block2){};
    ~IfExpression(){};
};

class WhileExpression : public Expression
{
private:
    Expression expr;
    Block block;

public:
    WhileExpression(Expression &expr, Block &block) : expr(expr), block(block){};
    ~WhileExpression(){};
};
