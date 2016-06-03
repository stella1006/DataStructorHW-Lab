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
using namespace std;


class Information { //student information
public:
	string id;
	string name;
	int age;
	bool gender;

	Information(string i = "", string n = "", int a = 0, bool g = 0) { //consturctor
		id = i;
		name = n;
		age = a;
		gender = g;
	}

	/*int getId() {
	int val = 0;
	for (int i = 0; i < 4; i++)
	val = val + pow(10, i) * (id[id.size() - 1 - i] - '0');
	}*/
};

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
		//cout << id << " " << name << " " << age << " " << sex << endl;
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


void read_stu(HashTable<Student> &h, HashTable2<string> & h2) {
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
		id = line.substr(0, 18);
		//v.push_back(id);
		name = line.substr(19, 6);
		
		temp = line.substr(26, 2);
		age = str_to_i(temp);

		
		temp = line[29];
		if (temp[0] == '0') sex = 0;
		else sex = 1;

		//cout << id << " " << name << " " << age << " " << sex << endl;
		Student stu(id, name, age, sex);
		//Information inf(id, name, age, sex);
		h.insert(stu);
		h2.insert(id);
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
	welcome();
	command_tips();
	cout << endl;
	srand(time(0));
	//create_stu();
	HashTable<Student> h;
	HashTable2<string> table;
	
	read_stu(h, table);
	
	//h.print();
	//h2.print();
	
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
					vector<list<Student> > ve = h.getList();
					string s1 = (*(ve[rand() % ve.size()].begin())).getID();
					clock_t start = clock();
					h.findKey(s1);
					clock_t end = clock();
					cout << "Time_with_Linked_list: " << (double)((double)(end - start) / CLOCKS_PER_SEC) << endl;

					clock_t start1 = clock();
					table.contains(s1); //search for the student in the table and output the result
					clock_t end1 = clock();
					double cpu_time_used = ((double)(end1 - start1)) / CLOCKS_PER_SEC; //compute the time for searching
					cout << "Time_with_Open_Address: " << cpu_time_used << endl;
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


	vector<list<Student> > ve = h.getList();
	string s1 = (*(ve[rand() % ve.size()].begin())).getID();
	string s2 = (*(ve[rand() % ve.size()].begin())).getID();

	
	//574829672648958765 stella 19 1
	system("pause");
	return 0;
}
