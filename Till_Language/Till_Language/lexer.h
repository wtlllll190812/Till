#pragma once
#include<iostream>
#include "token.h"

class lexer
{
public:
	lexer(std::string& text);

	/// <summary>
	/// 读取下一个token
	/// </summary>
	token get_next_token();

private:
	/// <summary>
	/// 读取下一个字符
	/// </summary>
	void read_char();

	/// <summary>
	/// 预读取下一个字符
	/// </summary>
	/// <returns></returns>
	char peek_char();
	
	/// <summary>
	/// 跳过空字符
	/// </summary>
	void skip_whitespace();

	/// <summary>
	/// 读取数字
	/// </summary>
	/// <returns>数字</returns>
	std::string read_number();

	/// <summary>
	/// 读取字符串
	/// </summary>
	/// <returns>字符串</returns>
	std::string read_string();

	/// <summary>
	/// 读取标识符
	/// </summary>
	/// <returns>标识符</returns>
	std::string read_identifier();

	/// <summary>
	/// 是否为字幕
	/// </summary>
	bool is_letter(char c);

	/// <summary>
	/// 是否为数字
	/// </summary>
	bool is_digit(char c);

private:
	std::string m_text;

	char m_current_char = '\0';		//当前字符
	int m_pos = 0;					//当前位置
	int m_next_pos = 0;				//下一个字符位置
};