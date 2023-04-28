#pragma once
#include <iostream>

class Identifier;

class Object
{
private:
    /* data */
public:
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
    /* data */
public:
    Block(){};
    ~Block(){};
    void Append(Statement *state){};
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
    /* data */
public:
    BinaryExpression(Expression &expr1, int &op, Expression &expr2){};
    BinaryExpression(Object &obj, int &op, Expression &expr){};
    BinaryExpression(Expression &expr, int &op, Object &obj){};
    ~BinaryExpression(){};
};

class ConstExpression : public Expression
{
private:
    /* data */
public:
    ConstExpression(Object &objct){};
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
    /* data */
public:
    IfExpression(Expression &expr, Block &block){};
    IfExpression(Expression &expr, Block &block1, Block &block2){};
    ~IfExpression(){};
};

class ObjectExpression : public Expression
{
private:
    /* data */
public:
    ObjectExpression(){};
    ~ObjectExpression(){};
};

class WhileExpression : public Expression
{
private:
    /* data */
public:
    WhileExpression(Expression &expr, Block &block){};
    ~WhileExpression(){};
};
