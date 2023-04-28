#pragma once
#include "ast_node.h"
#include <vector>

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

/// <summary>
/// 标识符
/// </summary>
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

/// <summary>
/// 整数
/// </summary>
class integerLiteral : public expression
{
public:
	integerLiteral(const token& token) : expression(token)
	{
		m_value = std::stoi(token.value);
	}
	~integerLiteral() override = default;

	std::string to_string() const override;
	const int value() const;

private:
	int m_value;
};

class block_statement;
/// <summary>
/// 函数定义
/// </summary>
class function_literal : public expression
{
public:
	std::string to_string() const override;
	void set_parameters(std::vector<std::shared_ptr<identifier>>& parameters);
	void set_body(block_statement* body);

private:
	mutable std::vector<std::shared_ptr<identifier>> m_parameters;
	mutable std::shared_ptr<block_statement> m_body;
};


