#include<iostream>
#include<fstream>
#include<string>
#include "lexer.h"
#include "parser.h"
using namespace std;

void read_file(string filepath, ifstream& infile);
void run_lex(ifstream& infile);
void run_parser(ifstream& infile);

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
	//run_lex(infile);
	run_parser(infile);

	infile.close();
	return 0;
}

/// <summary>
/// ��ȡtill�ļ�
/// </summary>
/// <param name="filepath">�ļ�·��</param>
void read_file(string filepath, ifstream& infile)
{
	infile.open(filepath, ios::in);

	if (!infile.is_open())
	{
		cout << "��ȡ�ļ�ʧ��" << endl;
	}
}

/// <summary>
/// ���дʷ�����
/// </summary>
void run_lex(ifstream& infile)
{
	string line;
	lexer m_lexer;

	while (getline(infile, line))
	{
		m_lexer.set_line(line);

		// ����ÿһ��Ϊtoken����ʾ
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

void run_parser(ifstream& infile)
{
	string line;
	parser m_parser;

	while (getline(infile, line))
	{
		auto program = m_parser.parse(line);
		cout << program->to_string() << endl;
	}
}