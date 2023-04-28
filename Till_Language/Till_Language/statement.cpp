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

std::string return_statement::to_string() const
{
    std::string ret = token_value();
    if (m_expression != nullptr)
    {
        ret += m_expression->to_string();
    }
    ret += ';';
    return ret;
}

void return_statement::set_expression(expression* expression)
{
    m_expression.reset(expression);
}

std::string expression_statment::to_string() const
{
    std::string ret="expression"; // ÁÙÊ±
    if (m_expression != nullptr)
    {
        ret = m_expression->to_string();
    }

    return ret;
}

void expression_statment::set_expression(expression* expression)
{
    m_expression.reset(expression);
}

std::string block_statement::to_string() const
{
    std::string ret;
    for (auto& stmt : m_statements)
    {
        ret += stmt->to_string();
    }
    return ret;
}

void block_statement::append(statement* statment)
{
    m_statements.emplace_back(statment);
}
