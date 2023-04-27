#include "lexer.h"
using namespace std;

lexer::lexer(std::string& text)
{
	m_text = text;
	read_char();
}

token lexer::next_token()
{
	skip_whitespace();
	token res;

	switch (m_current_char)
	{
	case '"':
		res = token(token::token_type::STRING, read_string());
		break;
	case '=':
		if(peek_char()=='=')
		res = token(token::token_type::ASSIGN, "=");
		break;
	case '+':
		res = token(token::token_type::PLUS, "+");
		break;
	case '-':
		res = token(token::token_type::MINUS, "-");
		break;
	case '!':
		res = token(token::token_type::BANG, "!");
		break;
	case '*':
		res = token(token::token_type::ASTERISK, "*");
		break;
	case '/':
		res = token(token::token_type::SLASH, "/");
		break;
	case '<':
		res = token(token::token_type::LT, "<");
		break;
	case '>':
		res = token(token::token_type::GT, ">");
		break;
	case ';':
		res = token(token::token_type::SEMICOLON, ";");
		break;
	case '(':
		res = token(token::token_type::LPAREN, "(");
		break;
	case ')':
		res = token(token::token_type::RPAREN, ")");
		break;
	case ',':
		res = token(token::token_type::COMMA, ",");
		break;
	case '{':
		res = token(token::token_type::LBRACE, "{");
		break;
	case '}':
		res = token(token::token_type::RBRACE, "}");
		break;
	case '[':
		res = token(token::token_type::LBRACKET, "[");
		break;
	case ']':
		res = token(token::token_type::RBRACKET, "]");
		break;
	case ':':
		res = token(token::token_type::COLON, ":");
		break;
	case 0:
		res = token(token::token_type::END, "");
		break;
	default:
		if (is_letter(m_current_char))
		{
			std::string ident = read_identifier();
			token::token_type type = token::lookup(ident);
			res = token(type, ident);
		}
		else if (is_digit(m_current_char))
		{
			res = token(token::token_type::INT, read_number());
		}
		else
		{
			res = token(token::token_type::ILLEGAL, "");
		}
		break;
	}

	read_char();
	return res;
}

lexer::~lexer()
{
}

void lexer::read_char()
{
	if (m_next_pos >= m_text.length())
	{
		m_current_char = 0;
	}
	else
	{
		m_current_char = m_text[m_next_pos];
	}

	m_pos = m_next_pos;
	m_next_pos++;
}

char lexer::peek_char()
{
	if (m_next_pos >= m_text.length())
	{
		return 0;
	}
	else
	{
		return m_text[m_next_pos];
	}
}

void lexer::skip_whitespace()
{
	while (m_current_char == ' ' ||
		m_current_char == '\t' ||
		m_current_char == '\n' ||
		m_current_char == '\r')
	{
		read_char();
	}
}

std::string lexer::read_number()
{
	int pos = m_pos;
	while (is_digit(m_current_char))
	{
		read_char();
	}
	return m_text.substr(pos, m_pos - pos);
}

std::string lexer::read_string()
{
	int pos= m_pos + 1;
	while (true)
	{
		read_char();
		if (m_current_char == '"')
		{
			break;
		}
	}
	return m_text.substr(pos, m_pos - pos);
}

std::string lexer::read_identifier()
{
	int pos = m_pos;
	while (is_letter(m_current_char))
	{
		read_char();
	}
	return m_text.substr(pos, m_pos - pos);
}

bool lexer::is_letter(char c)
{
	return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '_';
}

bool lexer::is_digit(char c)
{
	return '0' <= c && c <= '9';
}