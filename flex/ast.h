#pragma once
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

class BinaryExpression : public Expression
{
private:
    /* data */
public:
    BinaryExpression(){};
    ~BinaryExpression(){};
};

class IfExpression : public Expression
{
private:
    /* data */
public:
    IfExpression(){};
    ~IfExpression(){};
};

class FunctionExpression : public Expression
{
private:
    /* data */
public:
    FunctionExpression(){};
    ~FunctionExpression(){};
};

class CallExpression : public Expression
{
private:
    /* data */
public:
    CallExpression(){};
    ~CallExpression(){};
};

class WhileExpression : public Expression
{
private:
    /* data */
public:
    WhileExpression(){};
    ~WhileExpression(){};
};

class Identifier : public Expression
{
private:
    /* data */
public:
    Identifier(){};
    ~Identifier(){};
};

class AssignExpression : public Expression
{
private:
    /* data */
public:
    AssignExpression(){};
    ~AssignExpression(){};
};

class ObjectExpression : public Expression
{
private:
    /* data */
public:
    ObjectExpression(){};
    ~ObjectExpression(){};
};

class Block : public Node
{
private:
    /* data */
public:
    Block(){};
    ~Block(){};
};

class Statement : public Node
{
private:
    /* data */
public:
    Statement(){};
    ~Statement(){};
};