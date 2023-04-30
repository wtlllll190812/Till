#include "ast.h"
#include "parser.hpp"
#include <stdlib.h>
using namespace std;

typedef std::map<std::string, Object> Env_table;

std::string Object::get_value()
{
    return m_value;
}

bool Object::get_bool()
{
    if (m_type == Null || m_type == Error)
    {
        return false;
    }
    else if (m_type == Bool)
    {
        return m_value == "true";
    }
    else
    {
        return true;
    }
}

Object Object::operator=(const Object &obj)
{
    m_value = obj.m_value;
    m_type = obj.m_type;
    return *this;
}

Object Object::operator+(const Object &obj)
{
    Object ret;
    double value1;
    double value2;
    if (!operable(obj))
    {
        error_object("Type mismatch");
    }

    if (!str2double(m_value, value1) || !str2double(obj.m_value, value2))
    {
        if (m_type == String)
        {
            ret.m_type = String;
            ret.m_value = m_value + obj.m_value;
            return ret;
        }
        else
        {
            error_object("Type mismatch");
        }
    }

    ret.m_type = Double;
    ret.m_value = value1 + value2;
    return ret;
}

Object Object::operator-(const Object &obj)
{
    double value1;
    double value2;
    if (!operable(obj) || !str2double(m_value, value1) || !str2double(obj.m_value, value2))
    {
        error_object("Type mismatch");
    }

    Object ret;
    ret.m_type = Double;
    ret.m_value = value1 - value2;
    return ret;
}

Object Object::operator*(const Object &obj)
{
    double value1;
    double value2;
    if (!operable(obj) || !str2double(m_value, value1) || !str2double(obj.m_value, value2))
    {
        error_object("Type mismatch");
    }

    Object ret;
    ret.m_type = Double;
    ret.m_value = value1 * value2;
    return ret;
}

Object Object::operator/(const Object &obj)
{
    double value1;
    double value2;
    if (!operable(obj) || !str2double(m_value, value1) || !str2double(obj.m_value, value2))
    {
        error_object("Type mismatch");
    }

    Object ret;
    ret.m_type = Double;
    ret.m_value = value1 / value2;
    return ret;
}

Object Object::operator||(Object &obj)
{
    auto res = get_bool() || obj.get_bool();
    Object ret;
    ret.m_type = Object::Bool;
    ret.m_value = res ? "true" : "false";
    return ret;
}

Object Object::operator&&(Object &obj)
{
    auto res = get_bool() && obj.get_bool();
    Object ret;
    ret.m_type = Object::Bool;
    ret.m_value = res ? "true" : "false";
    return ret;
}

Object Object::operator!()
{
    auto res = !get_bool();
    Object ret;
    ret.m_type = Object::Bool;
    ret.m_value = res ? "true" : "false";
    return ret;
}

Object Object::operator==(Object &obj)
{
    auto res = obj.m_value == m_value && obj.m_type == m_type;
    Object ret;
    ret.m_type = Object::Bool;
    ret.m_value = res ? "true" : "false";
    return ret;
}

Object Object::operator>(Object &obj)
{
    if (!operable(obj))
    {
        error_object("Type mismatch");
    }

    auto res = stod(m_value) > stod(obj.m_value);
    Object ret;
    ret.m_type = Object::Bool;
    ret.m_value = res ? "true" : "false";
    return ret;
}

Object Object::operator<(Object &obj)
{
    if (!operable(obj))
    {
        error_object("Type mismatch");
    }

    auto res = stod(m_value) < stod(obj.m_value);
    Object ret;
    ret.m_type = Object::Bool;
    ret.m_value = res ? "true" : "false";
    return ret;
}

Object Object::operator>=(Object &obj)
{
    Object ret1 = operator>(obj);
    Object ret2 = operator==(obj);
    return ret1 || ret2;
}

Object Object::operator<=(Object &obj)
{
    Object ret1 = operator<(obj);
    Object ret2 = operator==(obj);
    return ret1 || ret2;
}

Object Object::operator!=(Object &obj)
{
    Object ret1 = operator==(obj);
    return !ret1;
}

bool Object::operable(const Object &obj)
{
    bool res = false;
    res |= m_type != obj.m_type;
    res |= m_type == Object::Null || obj.m_type == Object::Null;
    res |= m_type == Object::Error || obj.m_type == Object::Error;
    return !res;
}

bool Object::str2double(const std::string &str, double &value)
{
    try
    {
        value = std::stod(str);
    }
    catch (std::invalid_argument &e)
    {
        return false;
    }
    return true;
}

Object Object::error_object(const std::string errortext)
{
    Object ret;
    ret.m_type = Object::Error;
    ret.m_value = errortext;
    cout << errortext << endl;
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
        return Object();
    }
}