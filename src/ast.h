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
private:
    std::string ident;
    Expression *expr;
    int op;

public:
    AssignExpression(std::string &ident, int &op, Expression *&expr) : ident(ident), op(op), expr(expr){};
    ~AssignExpression(){};
    std::string toString() override
    {
        std::string ret;
        ret += "Assign: ";
        ret += ident;
        ret += " ";
        ret += std::to_string(op);
        ret += " ";
        ret += expr->toString();
        return ret;
    }
};

class BinaryExpression : public Expression
{
private:
    Expression *expr1;
    Expression *expr2;
    int op;

public:
    BinaryExpression(Expression *&expr1, int &op, Expression *&expr2)
        : expr1(expr1), expr2(expr2), op(op){};
    ~BinaryExpression(){};
    std::string toString() override
    {
        std::string ret;
        ret += "BinaryExpr: ";
        ret += expr1->toString();
        ret += " ";
        ret += std::to_string(op);
        ret += " ";
        ret += expr2->toString();
        return ret;
    }
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
        ret += "Let: ";
        ret += ident;
        ret += " = ";
        ret += expr->toString();
        return ret;
    }
};

class FunctionExpression : public Expression
{
private:
    std::string ident;
    std::vector<std::string> args;
    Block block;

public:
    FunctionExpression(std::string &ident, std::vector<std::string> &args, Block &block) : ident(ident), args(args), block(block){};
    ~FunctionExpression(){};
    std::string toString() override
    {
        std::string ret;
        ret += "Function: ";
        ret += ident;
        ret += "(";
        for (auto &arg : args)
        {
            ret += arg;
            ret += ", ";
        }
        ret += ")\n";
        ret += block.toString();
        return ret;
    }
};

class FunctionCallExpression : public Expression
{
private:
    std::string ident;
    std::vector<Expression *> args;

public:
    FunctionCallExpression(std::string &ident, std::vector<Expression *> &args) : ident(ident), args(args){};
    ~FunctionCallExpression(){};
    std::string toString() override
    {
        std::string ret;
        ret += "FunctionCall: ";
        ret += ident;
        ret += "(";
        for (auto &arg : args)
        {
            ret += arg->toString();
            ret += ", ";
        }
        ret += "\b)";
        return ret;
    }
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
        ret += "If: ";
        ret += expr->toString();
        ret += "\n\t";
        ret += block1.toString();
        ret += "else\n\t";
        ret += block2.toString();
        return ret;
    }
};

class ReturnExpression : public Expression
{
private:
    Expression *expr;

public:
    ReturnExpression(Expression *&expr) : expr(expr){};
    ~ReturnExpression(){};
    std::string toString() override
    {
        std::string ret;
        ret += "Return: ";
        ret += expr->toString();
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
