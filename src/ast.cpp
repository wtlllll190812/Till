#include "ast.h"
#include "parser.hpp"
#include <stdlib.h>
using namespace std;

typedef std::map<std::string, Object> Env_table;

Object Object::object_null = Object("", Object::Null);
Object Object::object_return = Object("", Object::Return);
Object Object::object_break = Object("", Object::Break);
std::vector<Object> Object::error_objects = vector<Object>();

std::string Object::get_value()
{
    return m_value;
}

Object::Type Object::get_type()
{
    return m_type;
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

void Object::operator=(const Object &obj)
{
    m_value = obj.m_value;
    m_type = obj.m_type;
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
    double value1;
    double value2;
    if (!operable(obj) || !str2double(m_value, value1) || !str2double(obj.m_value, value2))
    {
        error_object("Type mismatch");
    }

    Object ret;
    ret.m_type = Object::Bool;
    ret.m_value = value1 - value2 > 0 ? "true" : "false";
    return ret;
}

Object Object::operator<(Object &obj)
{
    double value1;
    double value2;
    if (!operable(obj) || !str2double(m_value, value1) || !str2double(obj.m_value, value2))
    {
        error_object("Type mismatch");
    }

    Object ret;
    ret.m_type = Object::Bool;
    ret.m_value = value1 - value2 < 0 ? "true" : "false";
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
    res |= m_type == Object::Null;
    res |= m_type == Object::Error;
    res |= m_type == Object::Break;
    res |= m_type == Object::Return;

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

Object &Object::error_object(const std::string errortext)
{
    cout << errortext << endl;
    error_objects.push_back(Object(errortext, Object::Error));
    return error_objects.back();
}

void Block::eval(Env &env)
{
    if (!m_init)
    {
        env.push_val(std::map<std::string, std::shared_ptr<Object>>());
        m_init = true;
    }

    for (auto &expr : exprs)
    {
        if ((expr->eval(env) == Object::object_return).get_bool())
            break;
    }
    env.pop_val();
}

void Block::env_init(Env &env, std::string &ident, Object object)
{
    if (!m_init)
    {
        env.push_val(std::map<std::string, std::shared_ptr<Object>>());
        m_init = true;
    }
    env.append_var(ident, shared_ptr<Object>(new Object(object)));
}

Object BinaryExpression::eval(Env &env)
{
    auto obj1 = expr1->eval(env);
    auto obj2 = expr2->eval(env);
    cout << obj1.get_value() << "___";
    cout << obj1.get_type() << endl;
    cout << obj2.get_value() << "___";
    cout << obj2.get_type() << endl;
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
    env.append_func(ident, args, block);
    return Object::object_null;
}

Object FunctionCallExpression::eval(Env &env)
{
    auto func = env.find_func(ident);
    for (int i = 0; i < args.size(); i++)
    {
        func->body.env_init(env, func->args[i], args[i]->eval(env));
    }
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
