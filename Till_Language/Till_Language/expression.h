#pragma once
#include "ast_node.h"

class expression : public ast_node
{
public:
	expression(const token& token) : m_token(token){}
	~expression() override = default;
	virtual std::string token_value() const override;
	virtual std::string to_string() const override;

protected:
	token m_token;
};

class identifier : public expression
{
public:
	identifier(const token& token, const std::string& value) : expression(token), _value(value)
	{
	}
	~identifier() override = default;

	std::string to_string() const override;
	const std::string& value() const;

private:
	std::string _value;
};