#include "object.h"
#include <iostream>
using namespace std;

Object Object::object_null = Object("", Object::Null);
Object Object::object_return = Object("", Object::Return);
Object Object::object_break = Object("", Object::Break);
vector<Object> Object::error_objects = vector<Object>();

string Object::get_value()
{
    return m_value;
}

Object::Type Object::get_type()
{
    return m_type;
}

void Object::set_value(string value)
{
    m_value = value;
}

void Object::set_type(Object::Type type)
{
    m_type = type;
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
    ret.m_value = to_string(value1 + value2);
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
    ret.m_value = to_string(value1 - value2);
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
    ret.m_value = to_string(value1 * value2);
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
    ret.m_value = to_string(value1 / value2);
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
    if ((m_type == Int && obj.m_type == Double) || (obj.m_type == Int && m_type == Double))
    {
        return true;
    }

    bool res = false;
    res |= m_type != obj.m_type;
    res |= m_type == Object::Null;
    res |= m_type == Object::Error;
    res |= m_type == Object::Break;
    res |= m_type == Object::Return;

    return !res;
}

bool Object::str2double(const string &str, double &value)
{
    try
    {
        value = stod(str);
    }
    catch (invalid_argument &e)
    {
        return false;
    }
    return true;
}

Object &Object::error_object(const string errortext)
{
    cout << errortext << endl;
    error_objects.push_back(Object(errortext, Object::Error));
    return error_objects.back();
}
