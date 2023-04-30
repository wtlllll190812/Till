#include "ast.h"
#include <stdlib.h>
using namespace std;

void Block::add_expr(Expression *expr)
{
    exprs.push_back(expr);
};

std::string Block::toString()
{
    std::string str = "";
    for (auto &expr : exprs)
    {
        str += expr->toString();
        str += "\n";
    }
    return str;
};

void Block::execute(Env &env)
{
    if (!m_init)
    {
        env.push_scope(std::map<std::string, std::shared_ptr<Object>>());
        m_init = true;
    }

    for (auto &expr : exprs)
    {
        if ((expr->execute(env) == Object::object_return).get_bool())
            break;
    }
    env.pop_scope();
    m_init = false;
}

void Block::env_init(Env &env, args_vec &args)
{
    if (!m_init)
    {
        env.push_scope(Scope());
        m_init = true;
    }
    for (auto &arg : args)
    {
        env.declare_var(arg.first, arg.second);
    }
}

std::string AssignExpression::toString()
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

Object AssignExpression::execute(Env &env)
{
    auto var = env.find_var(ident);
    auto obj = expr->execute(env);
    var->set_type(obj.get_type());
    var->set_value(obj.get_value());
    cout << "AssignExpression " << var->get_value() << endl;
    return Object::object_null;
}

std::string BinaryExpression::toString()
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

Object BinaryExpression::execute(Env &env)
{
    auto obj1 = expr1->execute(env);
    auto obj2 = expr2->execute(env);
    cout << "BinaryExpression " << obj1.get_value() << " " << op << " " << obj2.get_value() << endl;

    switch (op)
    {
    case (int)Opera::ADD:
        return obj1 + obj2;
    case (int)Opera::SUB:
        return obj1 - obj2;
    case (int)Opera::MUL:
        return obj1 * obj2;
    case (int)Opera::DIV:
        return obj1 / obj2;
    case (int)Opera::EQ:
        return obj1 == obj2;
    case (int)Opera::NE:
        return obj1 != obj2;
    case (int)Opera::GT:
        return obj1 > obj2;
    case (int)Opera::LT:
        return obj1 < obj2;
    case (int)Opera::GE:
        return obj1 >= obj2;
    case (int)Opera::LE:
        return obj1 <= obj2;
    default:
        return Object::object_null;
    }
}

std::string FunctionDeclareExpression::toString()
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

Object FunctionDeclareExpression::execute(Env &env)
{
    env.declare_func(ident, args, block);
    return Object::object_null;
}

std::string FunctionCallExpression::toString()
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

Object FunctionCallExpression::execute(Env &env)
{
    auto func = env.find_func(ident);
    auto args_decl = args_vec();
    for (int i = 0; i < args.size(); i++)
    {
        cout << func->args[i] << "  " << args[i]->execute(env).get_value() << endl;
        args_decl.push_back({func->args[i], shared_ptr<Object>(new Object(args[i]->execute(env)))});
    }
    func->body.env_init(env, args_decl);
    func->body.execute(env);
    return *env.get_return_val();
}

std::string IfExpression::toString()
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

Object IfExpression::execute(Env &env)
{
    if (expr->execute(env).get_bool() == true)
    {
        block1.execute(env);
    }
    else
    {
        block2.execute(env);
    }

    return Object::object_null;
}

std::string ReturnExpression::toString()
{
    std::string ret;
    ret += "Return: ";
    ret += expr->toString();
    return ret;
}

Object ReturnExpression::execute(Env &env)
{
    env.set_return_val(shared_ptr<Object>(new Object(expr->execute(env))));
    return Object::object_return;
}

std::string ValueExpression::toString()
{
    std::string ret;
    ret += obj.get_value();
    return ret;
}

Object ValueExpression::execute(Env &env)
{
    if (obj.get_type() == Object::Variable)
    {
        return *env.find_var(obj.get_value());
    }
    return obj;
}

std::string VarDeclareExpression::toString()
{
    std::string ret;
    ret += "Let: ";
    ret += ident;
    ret += " = ";
    ret += expr->toString();
    return ret;
}

Object VarDeclareExpression::execute(Env &env)
{
    env.declare_var(ident, std::shared_ptr<Object>(new Object(expr->execute(env))));
    return Object::object_null;
}

std::string WhileExpression::toString()
{
    std::string ret;
    ret += "While: ";
    ret += expr->toString();
    ret += "\n\t";
    ret += block.toString();
    return ret;
}

Object WhileExpression::execute(Env &env)
{
    while (expr->execute(env).get_bool() == true)
    {
        block.execute(env);
    }
    return Object::object_null;
}