#pragma once
#include <vector>
#include "ast_node.h"
#include "expression.h"

/// <summary>
/// ”Ôæ‰
/// </summary>
class statement : public ast_node
{
public:
	statement(const token& token) : m_token(token) {}
	virtual std::string token_value() const override;

protected:
	token m_token;
};

/// <summary>
/// let”Ôæ‰
/// </summary>
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

/// <summary>
/// return”Ôæ‰
/// </summary>
class return_statement : public statement
{
public:
	return_statement(token token) :statement(token) {};
	virtual std::string to_string() const override;

	void set_expression(expression* expression);
private:
	std::unique_ptr<expression> m_expression;
};

/// <summary>
/// ±Ì¥Ô Ω”Ôæ‰
/// </summary>
class expression_statment : public statement
{
public:
	expression_statment(token token) :statement(token) {};
	virtual std::string to_string() const override;

	void set_expression(expression* expression);
private:
	std::unique_ptr<expression> m_expression;
};

/// <summary>
/// ”Ôæ‰øÈ
/// </summary>
class block_statement : public statement
{
public:
	std::string to_string() const override;
	void append(statement* statment);

private:
    std::vector<std::unique_ptr<statement>> m_statements;
};