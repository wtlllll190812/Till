#include <unordered_map>
#include "parser.h"

// 优先级表
const std::unordered_map<token::token_type, parser::Precedence> PRECEDENCES = 
{
            {token::EQ, parser::Precedence::EQUALS},
            {token::NEQ, parser::Precedence::EQUALS},
            {token::LT, parser::Precedence::LESSGREATER},
            {token::GT, parser::Precedence::LESSGREATER},
            {token::LTE, parser::Precedence::LESSGREATER},
            {token::GTE, parser::Precedence::LESSGREATER},
            {token::PLUS, parser::Precedence::SUM},
            {token::MINUS, parser::Precedence::SUM},
            {token::SLASH, parser::Precedence::PRODUCT},
            {token::ASTERISK, parser::Precedence::PRODUCT},
            {token::LPAREN, parser::Precedence::CALL},
            {token::LBRACKET, parser::Precedence::INDEX},
};

parser::parser()
{
	lexer lex;
}

std::unique_ptr<program> parser::parse(std::string& line)
{
	m_line = line;
	init();
	auto program = std::make_unique<class program>();
	while (m_current_token.type != token::END)
	{
		auto stmt = parse_statement();
		if (stmt)
		{
			program->add_statement(stmt.release());
		}
		next_token();
	}

	return program;
}

void parser::init()
{
	m_lexer.set_line(m_line);

	m_current_token = m_lexer.get_next_token();
	m_next_token = m_lexer.get_next_token();
}

void parser::next_token()
{
	m_current_token = m_next_token;
	m_next_token = m_lexer.get_next_token();
}

std::unique_ptr<statement> parser::parse_statement()
{
    switch (m_current_token.type)
    {
    case token::LET:
        return parse_let_statment();
    case token::RETURN:
        return parse_return_statment();
    default:
        return parse_expression_statment();
    }

    return nullptr;
}

/// <summary>
/// 读取一个let关键字
/// </summary>
/// <returns></returns>
std::unique_ptr<statement> parser::parse_let_statment()
{
    std::unique_ptr<let_statement> stmt(new let_statement(m_current_token));

    // 查看下一个 token，并取出
    if (m_next_token.type != token::IDENT)
    {
        return nullptr;
    }
    next_token();

    stmt->set_identifier(new identifier(m_current_token, m_current_token.value));

    // 标识符的下一个 token 必须是 = 号
    if (m_next_token.type !=token::ASSIGN)
    {
        return nullptr;
    }

    // 跳过 = 号
    next_token();

    // 表达式解析部分
    auto exp = parse_expression(Precedence::LOWEST);
    stmt->set_expression(exp.release());

    if (m_next_token.type == token::SEMICOLON)
    {
        next_token();
    }

    return stmt;
}

std::unique_ptr<statement> parser::parse_return_statment()
{
    return std::unique_ptr<statement>();
}

std::unique_ptr<statement> parser::parse_expression_statment()
{
    return std::unique_ptr<statement>();
}

std::unique_ptr<expression> parser::parse_expression(Precedence precedence)
{
    return std::unique_ptr<expression>();
}
