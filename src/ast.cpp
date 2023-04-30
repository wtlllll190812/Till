#include "ast.h"
#include "parser.hpp"
#include <stdlib.h>
using namespace std;

typedef std::map<std::string, Object> Env_table;

void Block::eval(Env &env)
{
    if (!m_init)
    {
        env.push_scope(std::map<std::string, std::shared_ptr<Object>>());
        m_init = true;
    }

    for (auto &expr : exprs)
    {
        if ((expr->eval(env) == Object::object_return).get_bool())
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

Object AssignExpression::eval(Env &env)
{
    auto var = env.find_var(ident);
    auto obj = expr->eval(env);
    var->set_type(obj.get_type());
    var->set_value(obj.get_value());
    cout << "AssignExpression " << var->get_value() << endl;
    return Object::object_null;
}

Object BinaryExpression::eval(Env &env)
{
    auto obj1 = expr1->eval(env);
    auto obj2 = expr2->eval(env);
    cout << "BinaryExpression " << obj1.get_value() << " " << op << " " << obj2.get_value() << endl;

    switch (op)
    {
    case ADD:
        return obj1 + obj2;
    case SUB:
        return obj1 - obj2;
    case MUL:
        return obj1 * obj2;
    case DIV:
        return obj1 / obj2;
    case EQ:
        return obj1 == obj2;
    case NE:
        return obj1 != obj2;
    case GT:
        return obj1 > obj2;
    case LT:
        return obj1 < obj2;
    case GE:
        return obj1 >= obj2;
    case LE:
        return obj1 <= obj2;
    default:
        return Object::object_null;
    }
}

Object FunctionDeclareExpression::eval(Env &env)
{
    env.declare_func(ident, args, block);
    return Object::object_null;
}

Object FunctionCallExpression::eval(Env &env)
{
    auto func = env.find_func(ident);
    auto args_decl = args_vec();
    for (int i = 0; i < args.size(); i++)
    {
        cout << func->args[i] << "  " << args[i]->eval(env).get_value() << endl;
        args_decl.push_back({func->args[i], shared_ptr<Object>(new Object(args[i]->eval(env)))});
    }
    func->body.env_init(env, args_decl);
    func->body.eval(env);
    return *env.get_return_val();
}

Object ReturnExpression::eval(Env &env)
{
    env.set_return_val(shared_ptr<Object>(new Object(expr->eval(env))));
    return Object::object_return;
}

std::string ValueExpression::toString()
{
    std::string ret;
    ret += obj.get_value();
    return ret;
}
