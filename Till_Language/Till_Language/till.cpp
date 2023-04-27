#include<iostream>
#include<fstream>
#include<string>
#include "lexer.h"
using namespace std;

void read_file(string filepath);

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Usage: till <filename>" << endl;
		return 1;
	}

	string filename = argv[1];
	cout << "Reading file: " << filename << endl;

	read_file(filename);
	return 0;
}

/// <summary>
/// ��ȡtill�ļ�
/// </summary>
/// <param name="filepath">�ļ�·��</param>
void read_file(string filepath)
{
	ifstream infile;
	infile.open(filepath,ios::in);

	if (!infile.is_open())
	{
		cout << "��ȡ�ļ�ʧ��" << endl;
		return;
	}

	string line;
	while (getline(infile, line))
	{
		lexer lex(line);
		for (auto token = lex.next_token();
			token.type != token::token_type::END;
			token = lex.next_token()) 
		{
			std::cout << "{" <<token.type<< "}" << std::endl;
		}
	}
}