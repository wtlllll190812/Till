#include "program.h"
#include "statement.h"

std::string program::token_value() const
{
    if (m_statments.size() > 0)
    {
        return m_statments[0]->token_value();
    }
   
    return std::string();
}

std::string program::to_string() const
{
    // ·µ»ØËùÓĞÓï¾ä
    std::string ret;
    for (auto& state : m_statments)
    {
		ret += state->to_string();
	}

	return ret;
}

void program::add_statement(statement* state)
{
    m_statments.emplace_back(state);
}