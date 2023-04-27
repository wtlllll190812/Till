#pragma once
#include<iostream>
#include "token.h"

class lexer
{
public:
	lexer(std::string& text);
	token next_token();
	~lexer();

private:
	void read_char();
	char peek_char();
	void skip_whitespace();
	//void skip_comment();
	std::string read_number();
	std::string read_string();
	std::string read_identifier();
	bool is_letter(char c);
	bool is_digit(char c);

private:
	std::string m_text;

	char m_current_char = '\0';
	int m_pos = 0;
	int m_next_pos = 0;
};