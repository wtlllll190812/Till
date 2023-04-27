#pragma once
#include<iostream>
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

private:
	std::string m_line;
	token m_current_token;
	token m_next_token;
	lexer m_lexer;
};
