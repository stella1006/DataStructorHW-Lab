#include "HashTable.h"
#include "HashOpenAddress.h"
#include "HashTable2.h"
#include <iostream>
#include <ctime>
#include <cstring>
#include <fstream>
#include <ostream>
#include <windows.h>
#include <sstream>
#include <iomanip>
#include <Mmsystem.h>
#pragma comment(lib, "Winmm.lib")
using namespace std;
long long totalNumber;

void create_stu() {
	std::ofstream outfile;
	outfile.open("E://info.txt", ios::ate);
	for (int i = 0; i < 3000; i++) {
		Sleep(900);
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

	Student stu("", "", 0, 0);
}
int str_to_i(string s) {
	int res = 0;
	for (int i = 0; i < s.length(); i++) 
		res = res * 10 + (s[i]-'0');
	return res;
}


void read_stu(HashTable<Student> &h, HashTable2<Student> & h2) {
	std::ifstream infile;
	infile.open("E://info.txt", ios::in);
	string line;
	
	while(getline(infile, line)) {
		string id = "";
		string name = "";
		int age;
		int sex;
		string temp = "";
		int len = line.length();
		int i;
		id = line.substr(0, 18);
		name = line.substr(19, 6);
		
		temp = line.substr(26, 2);
		age = str_to_i(temp);

		temp = line[29];
		if (temp[0] == '0') sex = 0;
		else sex = 1;

		Student stu(id, name, age, sex);
		Student info(id, name, age, sex);
		h.insert(stu);
		h2.insert(info);
		totalNumber++;
		if (infile.eof()) {
			break;
		}
	}

	infile.close();
}

void welcome() {
	cout <<"***********************************************************" << endl;
	cout <<"*                                                         *" << endl;
	cout <<"*                                                         *" << endl;
	cout <<"*                          Welcome to                     *" << endl;
	cout <<"*           Student Driving Administration System         *" << endl;
	cout <<"*                                                         *" << endl;
	cout <<"*                                                         *" << endl;
	cout <<"*                               Numb: 14346009 14346022   *" << endl;
	cout <<"*                               Name:  ÀîÖ¾ÈÝ    Ì·Ð¦     *" << endl;
	cout <<"*                               Date:     2016.6.03       *" << endl;
	cout <<"***********************************************************" << endl;
	cout << endl;
}

void command_tips() {
	cout << "Please enter a command:" << endl;
	cout << "$Insert: insert a student's information" << endl;
	cout << "$Remove: remove a student's information" << endl;
	cout << "$Find: find a student's information" << endl;
	cout << "$Test: test two different ways used to solve the collision and compare their efficiency" << endl;
	cout << "$Quit: quit the system" << endl;
	cout << endl;
}

int main() {
	//create_stu();
	welcome();
	command_tips();
	cout << endl;
	srand(time(0));
	
	HashTable<Student> h;
	HashTable2<Student> table;
	
	//read_stu(h, table);
	
	string command;
	while(cin >> command) {
		if (command[0] == '$') {
			if (command[1] == 'Q') break;
			switch(command[1]) {
			case 'I':
				{
					cout << "Please input a student's information (ID, name, age, gender):" << endl;
					string id, name;
					int age;
					bool sex;
					cin >> id >> name >> age >> sex;
					Student student(id, name, age, sex);
					if (h.insert(student)) {
						cout << "\nInserted successfully: " << endl;  //print the information that is removed
						cout << "Name: " << student.getName() << endl;
						cout << "ID: " << student.getID() << endl;
						cout << "Age: " << student.getAge() << endl;
						cout << "Gender: " << (student.getSex() == 0? "Male":"Female") << endl <<  endl;
					} else {
						cout << "\nInserted failed: The system already contains the student" << endl;
					}

				}
				break;
			case 'R': 
				{
					cout << "Please input the student's ID:" << endl;
					string s2;
					cin >> s2;
					h.remove(s2);
					cout << endl;
				}
				break;
			case 'F':
				{
					cout << "Please input the student's ID:" << endl;
					string s2;
					cin >> s2;
					h.findKey(s2);
					cout << endl;
				}
				break;
			case 'T':
				{
					cout << "Please wait for inputing the information from the file." << endl;
					read_stu(h, table);
					cout << "Input finished" << endl;
					cout << "Tatal numbers of student: " << totalNumber << endl;
					vector<list<Student> > ve = h.getList();
					double ave_CHI = 0, ave_OPEN = 0;
					int num = 30;
					for (int i = 0; i < num; i++) {
						list<Student>::iterator p = ve[rand() % ve.size()].end();
						string s1 = (*(--p)).getID();
						double CHAIN, OPEN;
						ave_CHI += (double)h.cal_time(s1) ;
						ave_OPEN += (double)table.cal_time(s1);
						cout << "chaning: " << setw(8) << (double)h.cal_time(s1) << " s" << "   open addressing: " << setw(8) << (double)table.cal_time(s1) << " s" << endl;
						Sleep(100);
					}
					cout << "Average time with chaining: " << (double)(ave_CHI / num) << " s"<< endl;
					cout << "Average time with open addressing: " << (double)(ave_OPEN / num) << " s" << endl;
					
					
					cout << endl;
				} break;
			default:
				{
					cout << "Command error! Please enter a right command!" << endl;
					command_tips();
				} break;
			}
		} else {
			cout << "Command error! Please enter a right command!" << endl;
			command_tips();
		}
	}


	//574829672648958765 stella 19 1
	system("pause");
	return 0;
}
