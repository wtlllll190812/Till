#pragma once
#include <iostream>
#include <functional>
#include "env.h"
#include "object.h"

/// <summary>
/// operator
/// </summary>
enum class Opera
{
    ADD = 1,
    SUB = 2,
    MUL = 3,
    DIV = 4,
    EQ = 20,
    NE = 21,
    GT = 22,
    LT = 23,
    GE = 24,
    LE = 25,
};

/// <summary>
/// ast node
/// </summary>
class Node
{
public:
    Node(){};
    ~Node(){};
    virtual std::string toString() = 0;
};

/// <summary>
/// ast expression
/// </summary>
class Expression : public Node
{
public:
    Expression(){};
    ~Expression(){};
    virtual Object execute(Env &env) = 0;
};

/// <summary>
/// Block,contain some expressions
/// </summary>
class Block : public Node
{
private:
    bool m_init = false;

public:
    std::vector<Expression *> exprs;
    Block(){};
    ~Block(){};
    void add_expr(Expression *expr);

    std::string toString() override;
    void execute(Env &env);

    /// <summary>
    /// Init scope for block
    /// </summary>
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

    std::string toString() override;
    Object execute(Env &env) override;
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

    std::string toString() override;
    Object execute(Env &env) override;
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

    std::string toString() override;
    Object execute(Env &env) override;
};

class FunctionCallExpression : public Expression
{
private:
    std::string ident;
    std::vector<Expression *> args;

public:
    FunctionCallExpression(std::string &ident, std::vector<Expression *> &args) : ident(ident), args(args){};
    ~FunctionCallExpression(){};

    std::string toString() override;
    Object execute(Env &env) override;
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

    std::string toString() override;
    Object execute(Env &env) override;
};

class ReturnExpression : public Expression
{
private:
    Expression *expr;

public:
    ReturnExpression(Expression *&expr) : expr(expr){};
    ~ReturnExpression(){};

    std::string toString() override;
    Object execute(Env &env) override;
};

typedef std::map<std::string, std::function<Object(std::vector<Object>)>> SystemCallMap;

class SystemCallExpression : public Expression
{
private:
    std::string ident;
    std::vector<Expression *> args;
    static SystemCallMap syscalls;

public:
    SystemCallExpression(std::string &ident, std::vector<Expression *> &args) : ident(ident), args(args){};
    ~SystemCallExpression(){};

    std::string toString() override;
    Object execute(Env &env) override;
};

class ValueExpression : public Expression
{
private:
    Object obj;

public:
    ValueExpression(Object &obj) : obj(obj){};
    ~ValueExpression(){};

    std::string toString() override;
    Object execute(Env &env) override;
};

class VarDeclareExpression : public Expression
{
private:
    std::string ident;
    Expression *expr;

public:
    VarDeclareExpression(std::string &ident, Expression *&expression) : ident(ident), expr(expression){};
    ~VarDeclareExpression(){};

    std::string toString() override;
    Object execute(Env &env) override;
};

class WhileExpression : public Expression
{
private:
    Expression *expr;
    Block block;

public:
    WhileExpression(Expression *&expr, Block &block) : expr(expr), block(block){};
    ~WhileExpression(){};

    std::string toString() override;
    Object execute(Env &env) override;
};