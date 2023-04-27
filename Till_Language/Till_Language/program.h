#pragma once
#include <vector>
#include "ast_node.h"

class statement;
/// <summary>
/// ������ڵ㣬�������ɸ�statement
/// </summary>
class program: public ast_node
{
public:
	program() {};

	// ͨ�� node �̳�
	virtual std::string token_value() const override;
	virtual std::string to_string() const override;

	/// <summary>
	/// ���statement
	/// </summary>
	void add_statement(statement* state);

private:
	std::vector<std::unique_ptr<statement>> m_statments;
};