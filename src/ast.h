#pragma once
#include <iostream>
#include <vector>

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
    virtual std::string toString()
    {
        return "Expression";
    }
};

class Statement : public Node
{
private:
    Expression *expr;

public:
    Statement(Expression *&expr) : expr(expr){};
    ~Statement(){};
    std::string toString()
    {
        return expr->toString();
    }
};

class Block : public Node
{
public:
    std::vector<Statement *> statements;
    Block(){};
    ~Block(){};
    void Append(Statement *state)
    {
        statements.push_back(state);
    };

    std::string toString()
    {
        std::string str = "";
        for (auto &state : statements)
        {
            str += state->toString();
            str += "\n";
        }
        return str;
    };
};

class AssignExpression : public Expression
{
public:
    AssignExpression(std::string &ident, int &op, Expression *&expr){};
    ~AssignExpression(){};
};

class BinaryExpression : public Expression
{
private:
    Expression *expr1;
    Expression *expr2;
    Object obj;
    int op;

public:
    BinaryExpression(Expression *&expr1, int &op, Expression *&expr2)
        : expr1(expr1), expr2(expr2), op(op){};
    BinaryExpression(Object &obj, int &op, Expression *&expr)
        : expr1(expr), obj(obj), op(op){};
    BinaryExpression(Expression *&expr, int &op, Object &obj)
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

class DeclareExpression : public Expression
{
private:
    std::string ident;
    Expression *expr;

public:
    DeclareExpression(std::string &ident, Expression *&expression) : ident(ident), expr(expression){};
    ~DeclareExpression(){};

    std::string toString() override
    {
        std::string ret;
        ret += "DeclareExpression: ";
        ret += ident;
        ret += " = ";
        ret += expr->toString();
        return ret;
    }
};

class FunctionExpression : public Expression
{
private:
    /* data */
public:
    FunctionExpression(){};
    ~FunctionExpression(){};
};

class IfExpression : public Expression
{
private:
    Expression *expr;
    Block block1;
    Block block2;

public:
    IfExpression(Expression *expr, Block &block) : expr(expr), block1(block){};
    IfExpression(Expression *expr, Block &block1, Block &block2) : expr(expr), block1(block1), block2(block2){};
    ~IfExpression(){};
    std::string toString() override
    {
        std::string ret;
        ret += "IfExpression: ";
        ret += expr->toString();
        ret += "\n";
        ret += block1.toString();
        ret += "\n";
        ret += block2.toString();
        return ret;
    }
};

class WhileExpression : public Expression
{
private:
    Expression *expr;
    Block block;

public:
    WhileExpression(Expression *&expr, Block &block) : expr(expr), block(block){};
    ~WhileExpression(){};
};
