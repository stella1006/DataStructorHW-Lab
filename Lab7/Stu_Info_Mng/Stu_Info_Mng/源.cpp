#include "HashTable.h"
#include "HashOpenAddress.h"
#include <iostream>
#include <ctime>
#include <cstring>
#include <fstream>
#include <ostream>
#include <windows.h>
#include <sstream>
using namespace std;


void create_stu() {
	std::ofstream outfile;
	outfile.open("E://info.txt", ios::ate);
	for (int i = 0; i < 300; i++) {
		Sleep(800);
		srand(time(0));
		string id = "";
		string name = "";
		int age;
		int sex;

		for (int i = 0; i < 18; i++) {
			id += '0'+ rand() % 10;
		}
		for (int i = 0; i < 6; i++) {
			name += 'a' + rand() % 26;
		}

		age = rand() % 30 + 18;
		sex = rand() % 2;
		outfile << id << " " << name << " " << age << " " << sex << endl;
	}
	outfile.close();

	//Student stu(id, name, age, sex);
	Student stu("", "", 0, 0);
}
int str_to_i(string s) {
	//cout << s << endl;
	int res = 0;
	for (int i = 0; i < s.length(); i++) {
		res = res * 10 + (s[i]-'0');
	}
	return res;

}


void read_stu(HashTable<Student> &h, HashOpen<Student> & h2) {
	std::ifstream infile;
	infile.open("E://info.txt", ios::in);
	string line;
	
	
	while(getline(infile, line)) {
		//if (infile.fail()) break;
		//cout << line << endl;
		string id = "";
		string name = "";
		int age;
		int sex;
		string temp = "";
		int len = line.length();
		int i;
		for (i = 0; i < len && line[i] != ' '; i++) {
			id += line[i];
		}
		//v.push_back(id);
		for (i = i + 1; i < len && line[i] != ' '; i++) {
			name += line[i];
		}
		temp = "";
		for (i = i + 1; i < len && line[i] != ' '; i++) {
			temp += line[i];
		}
		
		age = str_to_i(temp);

		temp = "";
		for (i = i+1; i < len && line[i] != ' '; i++) {
			if (line[i] == ' ') {
				break;
			}
			else temp += line[i];
		}
		if (temp[0] == '0') sex = 0;
		else sex = 1;

		//cout << id << " " << name << " " << age << " " << sex << endl;
		Student stu(id, name, age, sex);
		h.insert(stu);
		h2.insert(stu);
		//line = "";
		if (infile.eof()) {
			break;
			//cin.get();
		}
		//cin.get();
		
	}

	infile.close();
	//cin.get();
	//Student stu(id, name, age, sex);
}



int main() {
	//vector<string> ve;
	//create_stu();
	HashTable<Student> h;
	HashOpen<Student> h2;
	
	read_stu(h, h2);
	//cout << 2 << endl;
	//int index = rand() % (ve.size());
	//string sd = ve[index];
	
	//h.print();
	//h2.print();
	//cout << 2 << endl;
	//cout << ve.size() << " " << index << endl;
	int start = clock();
	h.findKey("046807217364248671");
	int end = clock();
	cout << "list:" << " " << end - start << endl;
	
	int start1 = clock();
	h2.findKey("046807217364248671");
	int end1 = clock();
	cout << "open:" << " " << end1 - start1 << endl;

	//////h.findKey("000000000000060025");
	//////h.remove(stu1);
	//////h.print();
	//////h.findKey("000000000000060024");
	system("pause");
	return 0;
}
