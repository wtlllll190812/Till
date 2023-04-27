#pragma once
#include<iostream>
#include "token.h"

class lexer
{
public:
	lexer(std::string& text);

	/// <summary>
	/// ��ȡ��һ��token
	/// </summary>
	token get_next_token();

private:
	/// <summary>
	/// ��ȡ��һ���ַ�
	/// </summary>
	void read_char();

	/// <summary>
	/// Ԥ��ȡ��һ���ַ�
	/// </summary>
	/// <returns></returns>
	char peek_char();
	
	/// <summary>
	/// �������ַ�
	/// </summary>
	void skip_whitespace();

	/// <summary>
	/// ��ȡ����
	/// </summary>
	/// <returns>����</returns>
	std::string read_number();

	/// <summary>
	/// ��ȡ�ַ���
	/// </summary>
	/// <returns>�ַ���</returns>
	std::string read_string();

	/// <summary>
	/// ��ȡ��ʶ��
	/// </summary>
	/// <returns>��ʶ��</returns>
	std::string read_identifier();

	/// <summary>
	/// �Ƿ�Ϊ��Ļ
	/// </summary>
	bool is_letter(char c);

	/// <summary>
	/// �Ƿ�Ϊ����
	/// </summary>
	bool is_digit(char c);

private:
	std::string m_text;

	char m_current_char = '\0';		//��ǰ�ַ�
	int m_pos = 0;					//��ǰλ��
	int m_next_pos = 0;				//��һ���ַ�λ��
};