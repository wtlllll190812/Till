#include "expression.h"

std::string expression::token_value() const
{
    return std::string();
}

std::string expression::to_string() const
{
    return std::string();
}

std::string identifier::to_string() const
{
    return _value;
}

const std::string& identifier::value() const
{
    return _value;
}
