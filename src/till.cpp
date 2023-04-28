#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ast.hpp"
#include "parser.hpp"

extern Block *program;

using namespace std;

void read_file(string filepath, ifstream &infile);

int main(int argc, char *argv[])
{
	yyparse();
	std::cout << "sdsdsdsd" << std::endl;
	return 0;

	// if (argc < 2)
	// {
	// 	cout << "Usage: till <filename>" << endl;
	// 	return 1;
	// }

	// string filename = argv[1];
	// cout << "Reading file: " << filename << endl;
	// ifstream infile;

	// read_file(filename, infile);

	// infile.close();
	// return 0;
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