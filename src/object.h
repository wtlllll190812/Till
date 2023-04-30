#pragma once
#include <string>
#include <vector>

class Object
{
public:
    enum Type
    {
        Error,
        Null,
        Return,
        Break,

        String,
        Int,
        Double,
        Bool,

        Variable,
        Function,
    };

public:
    static Object object_null;
    static Object object_return;
    static Object object_break;

private:
    std::string m_value;
    Type m_type;

public:
    Object() : m_value(""), m_type(Null){};
    Object(std::string value, Type type) : m_value(value), m_type(type){};
    ~Object(){};
    void operator=(const Object &obj);
    Object operator+(const Object &obj);
    Object operator-(const Object &obj);
    Object operator*(const Object &obj);
    Object operator/(const Object &obj);
    Object operator||(Object &obj);
    Object operator&&(Object &obj);
    Object operator!();
    Object operator==(Object &obj);
    Object operator>(Object &obj);
    Object operator<(Object &obj);
    Object operator>=(Object &obj);
    Object operator<=(Object &obj);
    Object operator!=(Object &obj);

    std::string get_value();
    Type get_type();
    bool get_bool();
    void set_value(std::string value);
    void set_type(Object::Type type);

    static Object &error_object(const std::string errortext);

private:
    bool operable(const Object &obj);
    bool str2double(const std::string &str, double &value);
    static std::vector<Object> error_objects;
};
