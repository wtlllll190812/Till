#pragma once
#include<iostream>
#include "token.h"
#include "program.h"

class parser
{
public:
	parser(std::string& line);
	std::unique_ptr<program> progrom(new program());
private: 
	
private:
	std::string m_line;
	token m_current_token;
	token m_next_token;
};
