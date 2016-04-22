#ifndef EDITOR_H
#define EDITOR_H

#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <ostream>
#include <iostream>
using namespace std;

class Editor {
public:
	Editor();//后置条件，编辑器为空
	Editor(const string &in, const string &out);
	string parse(const string& line);//如果line为合法命令，则该命令被执行，执行结果被返回。若line是插入的文本行，则该文本行被插入并返回结果；否则返回非法命令错误
	bool run_command();
	
	/*
	Editor(char *in, char *out);

	}

	*/
protected:
	string command_check(const string& line);//后置条件：检查line是否有错误。如果不存在错误，则命令被执行，错误被返回；否则，一个错误信息被返回
	void insert_command(const string& line);//如果line不是很长，则将其插入编辑器，并返回一个空行；否则，返回错误信息。
	void delete_command(int k, int m);//如可能，删除第k至m行，并返回一个空行，否则返回错误信息。
	void line_command(int m);//后置条件：如可能，第m行成为当前行，并返回一个空行；否则，返回错误信息
	void done_command();//编辑器运行结束，并返回文本
	bool str_to_int(string s, int a[], int n);//将s中的数字提取出来放到a[]中，n为数字的个数，如果含有非数字的字符，返回false
	void print_line(int start, int end);//打印从start到end行
	void quit();//退出
	void save();//将文本存盘
	void open();//打开一个新文件

public:
	list<string> text;//文本列表
	list<string>::iterator current;//当前行的迭代器
	int currentLineNumber;//当前文本行数
	bool inserting;//判断当前操作是否是插入操作
	string in, out;//输入输出文件名
	std::ifstream infile;//输入文件流
	std::ofstream outfile;//输出文件流


};

#endif // !EDITOR.H
