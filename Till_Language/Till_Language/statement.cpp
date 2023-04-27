#include "statement.h"
#include "expression.h"

std::string statement::token_value() const
{
    return m_token.value;
}

std::string let_statement::to_string() const
{
    std::string ret = token_value() + ' ' + m_identifier->to_string() + " = ";
    if (m_expression != nullptr)
    {
        ret += m_expression->to_string();
    }
    ret += ';';
    return ret;
}

std::string let_statement::token_value() const
{
    return m_token.value;
}

void let_statement::set_identifier(identifier* ident)
{
    m_identifier.reset(ident);
}

void let_statement::set_expression(expression* expression)
{
    m_expression.reset(expression);
}