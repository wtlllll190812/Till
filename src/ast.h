#pragma once
#include <iostream>
#include <vector>
#include "env.h"
#include "object.h"

class Node
{
private:
public:
    Node(){};
    ~Node(){};
};

class Expression : public Node
{
public:
    Expression(){};
    ~Expression(){};
    virtual std::string toString()
    {
        return "Expression";
    }
    virtual Object eval(Env &env) = 0;
};

class Block : public Node
{
private:
    bool m_init = false;

public:
    std::vector<Expression *> exprs;
    Block(){};
    ~Block(){};
    void Append(Expression *expr)
    {
        exprs.push_back(expr);
    };

    std::string toString()
    {
        std::string str = "";
        for (auto &expr : exprs)
        {
            str += expr->toString();
            str += "\n";
        }
        return str;
    };

    void eval(Env &env);
    void env_init(Env &env, args_vec &args);
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

    Object eval(Env &env) override;
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
    Object eval(Env &env) override;
};

class FunctionDeclareExpression : public Expression
{
private:
    std::string ident;
    std::vector<std::string> args;
    Block block;

public:
    FunctionDeclareExpression(std::string &ident, std::vector<std::string> &args, Block &block) : ident(ident), args(args), block(block){};
    ~FunctionDeclareExpression(){};
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
    Object eval(Env &env) override;
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
        ret += ")";
        return ret;
    }
    Object eval(Env &env) override;
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
    Object eval(Env &env) override
    {
        if (expr->eval(env).get_bool() == true)
        {
            block1.eval(env);
        }
        else
        {
            block2.eval(env);
        }

        return Object::object_null;
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
    Object eval(Env &env) override;
};

class ValueExpression : public Expression
{
private:
    Object obj;

public:
    ValueExpression(Object &obj) : obj(obj){};
    ~ValueExpression(){};
    std::string toString() override;
    Object eval(Env &env)
    {
        if (obj.get_type() == Object::Variable)
        {
            return *env.find_var(obj.get_value());
        }
        return obj;
    }
};

class VarDeclareExpression : public Expression
{
private:
    std::string ident;
    Expression *expr;

public:
    VarDeclareExpression(std::string &ident, Expression *&expression) : ident(ident), expr(expression){};
    ~VarDeclareExpression(){};

    std::string toString() override
    {
        std::string ret;
        ret += "Let: ";
        ret += ident;
        ret += " = ";
        ret += expr->toString();
        return ret;
    }

    Object eval(Env &env) override
    {
        env.declare_var(ident, std::shared_ptr<Object>(new Object(expr->eval(env))));
        return Object::object_null;
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
    Object eval(Env &env) override
    {
        while (expr->eval(env).get_bool() == true)
        {
            block.eval(env);
        }
        return Object::object_null;
    }
};