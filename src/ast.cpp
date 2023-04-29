#include "ast.h"
#include <stdlib.h>
using namespace std;

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

bool Object::mis_match(const Object &obj)
{
    return m_type != obj.m_type || m_type == Object::Null || obj.m_type == Object::Null;
}

std::string ValueExpression::toString()
{
    std::string ret;
    ret += obj.get_value();
    return ret;
}
