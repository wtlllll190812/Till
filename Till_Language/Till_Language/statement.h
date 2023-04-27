#pragma once
#include <vector>
#include "ast_node.h"
#include "expression.h"

/// <summary>
/// Óï¾ä
/// </summary>
class statement : public ast_node
{
public:
	statement(const token& token) : m_token(token) {}
	virtual std::string token_value() const override;

protected:
	token m_token;
};

class let_statement : public statement
{
public:
	let_statement(token token) :statement(token) {};
	virtual std::string to_string() const override;
	virtual std::string token_value() const override;

	void set_identifier(identifier* ident);
	void set_expression(expression* expression);

private:
	std::unique_ptr<identifier> m_identifier;
	std::unique_ptr<expression> m_expression;
};