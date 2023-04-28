#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include "lexer.h"
using namespace std;

void read_file(string filepath, ifstream& infile);
void run_lex(ifstream& infile);

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Usage: till <filename>" << endl;
		return 1;
	}

	string filename = argv[1];
	cout << "Reading file: " << filename << endl;
	ifstream infile;

	read_file(filename, infile);
	run_lex(infile);

	infile.close();
	return 0;
}

/// <summary>
/// 读取till文件
/// </summary>
/// <param name="filepath">文件路径</param>
void read_file(string filepath, ifstream& infile)
{
	infile.open(filepath, ios::in);

	if (!infile.is_open())
	{
		cout << "读取文件失败" << endl;
	}
}

/// <summary>
/// 运行词法分析
/// </summary>
void run_lex(ifstream& infile)
{
	string line;
	lexer m_lexer;

	while (getline(infile, line))
	{
		m_lexer.set_text(line);

		// 处理每一行为token并显示
		for (auto new_token = m_lexer.get_next_token();
			new_token.type != token::END;
			new_token = m_lexer.get_next_token())
		{
			std::cout << new_token << std::endl;
			if (new_token.type == token::ILLEGAL)
			{
				cout << "ILLEGAL" << endl;
				break;
			}
		}
	}
}