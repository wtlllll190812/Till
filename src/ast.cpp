#include "ast.h"
#include "parser.hpp"
#include <stdlib.h>
using namespace std;

typedef std::map<std::string, Object> Env_table;

std::string Object::get_value()
{
    return m_value;
}

Object Object::operator=(const Object &obj)
{
    m_value = obj.m_value;
    m_type = obj.m_type;
    return *this;
}

Object Object::operator+(const Object &obj)
{
    if (mis_match(obj))
    {
        Object ret;
        ret.m_type = Object::Error;
        ret.m_value = "Type mismatch";
        return ret;
    }

    Object ret;
    ret.m_type = m_type;
    ret.m_value = stod(m_value) + stod(obj.m_value);
    return ret;
}

Object Object::operator-(const Object &obj)
{
    if (mis_match(obj))
    {
        Object ret;
        ret.m_type = Object::Error;
        ret.m_value = "Type mismatch";
        return ret;
    }

    Object ret;
    ret.m_type = m_type;
    ret.m_value = stod(m_value) - stod(obj.m_value);
    return ret;
}

Object Object::operator*(const Object &obj)
{
    if (mis_match(obj))
    {
        Object ret;
        ret.m_type = Object::Error;
        ret.m_value = "Type mismatch";
        return ret;
    }

    Object ret;
    ret.m_type = m_type;
    ret.m_value = stod(m_value) * stod(obj.m_value);
    return ret;
}

Object Object::operator/(const Object &obj)
{
    if (mis_match(obj))
    {
        Object ret;
        ret.m_type = Object::Error;
        ret.m_value = "Type mismatch";
        return ret;
    }

    Object ret;
    ret.m_type = m_type;
    ret.m_value = stod(m_value) / stod(obj.m_value);
    return ret;
}

void Block::eval(Env &env)
{
    if (!m_init)
    {
        auto new_env = std::map<std::string, Object>();
        env.push_back(new_env);
        m_init = true;
    }

    for (auto &expr : exprs)
    {
        expr->eval(env);
    }
    env.pop_back();
}

void Block::env_init(Env &env, std::string &ident, Object &object)
{
    if (!m_init)
    {
        auto new_env = std::map<std::string, Object>();
        env.push_back(new_env);
        m_init = true;
    }
    env.append_ident(ident, object);
}

bool Object::mis_match(const Object &obj)
{
    return m_type != obj.m_type || m_type == Object::Null || obj.m_type == Object::Null || m_type == Object::Error || obj.m_type == Object::Error;
}

std::string ValueExpression::toString()
{
    std::string ret;
    ret += obj.get_value();
    return ret;
}

Object BinaryExpression::eval(Env &env)
{
    auto obj1 = expr1->eval(env);
    auto obj2 = expr2->eval(env);
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
    default:
        return Object();
    }
}
