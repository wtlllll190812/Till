#pragma once
#include <vector>
#include "ast_node.h"

class statement;
/// <summary>
/// 程序根节点，包含若干个statement
/// </summary>
class program: public ast_node
{
public:
	program() {};

	// 通过 node 继承
	virtual std::string token_value() const override;
	virtual std::string to_string() const override;

	/// <summary>
	/// 添加statement
	/// </summary>
	void add_statement(statement* state);

private:
	std::vector<std::unique_ptr<statement>> m_statments;
};