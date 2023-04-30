#pragma once
#include <string>
#include <vector>

class Object
{
public:
    enum Type
    {
        Error = -1,
        Null = 0,

        String = 1,
        Int = 2,
        Double = 3,
        Bool = 4,

        Variable = 11,
        Function = 12,
        Return = 13,
        Break = 14,
    };

public:
    static Object object_null;
    static Object object_return;
    static Object object_break;

private:
    static std::vector<Object> error_objects;

private:
    std::string m_value;
    Type m_type;

public:
    static Object &error_object(const std::string errortext);
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
    void set_value(std::string value);
    void set_type(Object::Type type);
    bool get_bool();

private:
    bool operable(const Object &obj);
    bool str2double(const std::string &str, double &value);
};
