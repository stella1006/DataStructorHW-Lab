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
	Editor();//�����������༭��Ϊ��
	Editor(const string &in, const string &out);
	string parse(const string& line);//���lineΪ�Ϸ����������ִ�У�ִ�н�������ء���line�ǲ�����ı��У�����ı��б����벢���ؽ�������򷵻طǷ��������
	bool run_command();
	
	/*
	Editor(char *in, char *out);

	}

	*/
protected:
	string command_check(const string& line);//�������������line�Ƿ��д�����������ڴ��������ִ�У����󱻷��أ�����һ��������Ϣ������
	void insert_command(const string& line);//���line���Ǻܳ����������༭����������һ�����У����򣬷��ش�����Ϣ��
	void delete_command(int k, int m);//����ܣ�ɾ����k��m�У�������һ�����У����򷵻ش�����Ϣ��
	void line_command(int m);//��������������ܣ���m�г�Ϊ��ǰ�У�������һ�����У����򣬷��ش�����Ϣ
	void done_command();//�༭�����н������������ı�
	bool str_to_int(string s, int a[], int n);//��s�е�������ȡ�����ŵ�a[]�У�nΪ���ֵĸ�����������з����ֵ��ַ�������false
	void print_line(int start, int end);//��ӡ��start��end��
	void quit();//�˳�
	void save();//���ı�����
	void open();//��һ�����ļ�

public:
	list<string> text;//�ı��б�
	list<string>::iterator current;//��ǰ�еĵ�����
	int currentLineNumber;//��ǰ�ı�����
	bool inserting;//�жϵ�ǰ�����Ƿ��ǲ������
	string in, out;//��������ļ���
	std::ifstream infile;//�����ļ���
	std::ofstream outfile;//����ļ���


};

#endif // !EDITOR.H
