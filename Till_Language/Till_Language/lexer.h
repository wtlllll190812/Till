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
	void read_next();
	void skip_whitespace();
	//void skip_comment();
	void read_identifier();
	void read_number();
	void read_string();

private:
	std::string m_text;

	char m_current_char;
	int m_pos;
	int m_next_pos;
};