#include <iostream>
#include <cstring>
#include "Editor.h"
using namespace std;

int main() {
	cout <<"***********************************************************" << endl;
	cout <<"*                                                         *" << endl;
	cout <<"*                                                         *" << endl;
	cout <<"*                    Simple Text Editor                   *" << endl;
	cout <<"*                                                         *" << endl;
	cout <<"*                   Welcome to have a try £¡              *" << endl;
	cout <<"*                                                         *" << endl;
	cout <<"*                               Numb: 14346009 14346022   *" << endl;
	cout <<"*                               Name:  ÀîÖ¾ÈÝ    Ì·Ð¦     *" << endl;
	cout <<"*                               Date:     2016.3.19       *" << endl;
	cout <<"***********************************************************" << endl;
	cout << endl;
	
	//Editor myEditor("E:\\2333.txt", "E:\\2333.txt");
	//string file = "E:\\2333.txt";
	//string in, out;
	//cin >> in >> out;
	//cin.get();
	Editor myEditor("", "");
	myEditor.run_command();

	system("pause");
	return 0;
}
