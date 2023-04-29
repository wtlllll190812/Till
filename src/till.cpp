#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include "ast.hpp"
#include "parser.hpp"
using namespace std;

extern Block *program;
extern int yyrestart(FILE *f);
extern int yydebug;

void read_file(string filepath, ifstream &infile);

int main(int argc, char *argv[])
{
	yydebug = 1;

	if (argc < 2)
	{
		cout << "Usage: till <filename>" << endl;
		return 1;
	}
	cout << "Reading file: " << argv[1] << endl;

	FILE *f;
	f = fopen(argv[1], "r");

	yyrestart(f);
	yyparse();
	std::cout << program->toString() << std::endl;

	fclose(f);
	return 0;
}

/// <summary>
/// 读取文件
/// </summary>
/// <param name="filepath">文件路径</param>
void read_file(string filepath, ifstream &infile)
{
	infile.open(filepath, ios::in);

	if (!infile.is_open())
	{
		cout << "文件打开失败" << endl;
	}
	cout << "打开文件" << endl;
}