#include "expression.h"
#include "statement.h"

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

std::string integerLiteral::to_string() const
{
    return m_token.value;
}

const int integerLiteral::value() const
{
    return m_value;
}

std::string function_literal::to_string() const
{
    if (m_body == nullptr)
    {
        return std::string();
    }

    std::string ret(m_token.value);

    ret.append(1, '(');
    for (size_t i = 0; i < m_parameters.size(); ++i)
    {
        if (i != 0)
        {
            ret.append(", ");
        }
        ret.append(m_parameters[i]->to_string());
    }
    ret.append(") { ");
    ret.append(m_body->to_string());
    ret.append(" }");
    return ret;
}

void function_literal::set_parameters(std::vector<std::shared_ptr<identifier>>& parameters)
{
    m_parameters = parameters;
}

void function_literal::set_body(block_statement* body)
{
    m_body.reset(body);
}
