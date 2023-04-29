#include "ast.h"
using namespace std;

std::string Object::get_value()
{
    return m_value;
}

std::string ValueExpression::toString()
{
    std::string ret;
    ret += obj.get_value();
    return ret;
}
