#include "HashTable.h"
#include "HashOpenAddress.h"
#include <iostream>
using namespace std;

int main() {
	HashTable<Student> h;
	Student stu1("000000000000060024", "stella", 19, 1);
	Student stu2("000000000000060025", "stella2", 19, 1);
	h.insert(stu1);
	h.insert(stu2);
	h.print();
	h.findKey("000000000000060024");
	h.findKey("000000000000060025");
	h.remove(stu1);
	h.print();
	h.findKey("000000000000060024");
	system("pause");
	return 0;
}
