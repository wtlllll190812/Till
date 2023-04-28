#pragma once
#include <iostream>
#include <functional>
#include "token.h"
#include "lexer.h"
#include "program.h"
#include "statement.h"
#include "expression.h"

class program;
class parser
{
public:
    enum Precedence
    {
        UNKNOWN = 0,
        LOWEST,
        EQUALS,      // ==
        LESSGREATER, // < or >
        SUM,         // +
        PRODUCT,     // *
        PREFIX,      // -x or !x
        CALL,        // fn(x)
        INDEX,       // array[index]
    };

public:
	parser();
	std::unique_ptr<program> parse(std::string& line);

private:
	void init();
    void next_token();
	std::unique_ptr<statement> parse_statement();
    std::unique_ptr<statement> parse_let_statment();
    std::unique_ptr<statement> parse_return_statment();
    std::unique_ptr<statement> parse_expression_statment();
    std::unique_ptr<expression> parse_expression(Precedence precedence);
    std::vector<std::shared_ptr<identifier>> parse_function_parameters();
    std::unique_ptr<block_statement> parse_block_statement();

    parser::Precedence current_precedence() const;
    parser::Precedence peek_precedence() const;

private:
    // 注册函数
    std::unique_ptr<expression> parse_identifier();
    std::unique_ptr<expression> parse_integer_literal();
    std::unique_ptr<expression> parse_string_literal();
    std::unique_ptr<expression> parse_boolean_literal();
    std::unique_ptr<expression> parse_function_literal();
    std::unique_ptr<expression> parse_array_literal();
    std::unique_ptr<expression> parse_hash_literal();
    std::unique_ptr<expression> parse_group_expression();
    std::unique_ptr<expression> parse_prefix_expression();
    std::unique_ptr<expression> parse_if_expression();
    std::unique_ptr<expression> parse_infix_expression(expression* left);
    std::unique_ptr<expression> parse_call_expression(expression* left);
    std::unique_ptr<expression> parse_index_expression(expression* left);

private:
    using PrefixParseFunc = std::function<std::unique_ptr<expression>()>;
    using InfixParseFunc = std::function<std::unique_ptr<expression>(expression* expression)>;

    // 用于解析前缀操作符
    std::map<token::token_type, PrefixParseFunc> _prefix_parse_funcs;
    // 用于解析后缀操作符
    std::map<token::token_type, InfixParseFunc> _infix_parse_funcs;

	std::string m_line;
	token m_current_token;
	token m_next_token;
	lexer m_lexer;
};