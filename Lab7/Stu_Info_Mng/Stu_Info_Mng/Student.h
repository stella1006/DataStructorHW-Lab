#ifndef  STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>
using namespace std;

class Student {
public:
	Student(string id="", string n="", int a=0, bool s=0) {
		ID = id;
		name = n;
		age = a;
	    sex = s;
	}

	const string & getID() const{
		return ID;
	}

	const string & getName() const{
		return name;
	}

	const int & getAge() const{
		return age;
	}

	const bool & getSex() const{
		return sex;
	}

	bool operator == (const Student & stu) const{
		return (getID() == stu.getID());
	}

	bool operator != (const Student & stu) const {
		return !(*this == stu);
	}


private:
	string ID;   //student's ID nember
	string name;  //student's name
	int age;     //student's age
	bool sex; //0 stands for male, 1 stands for female

};


#endif STUDENT_H