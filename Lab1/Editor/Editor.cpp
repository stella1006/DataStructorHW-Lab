#include "Editor.h"

const string PROMPT = "Please enter a line:";
const string NOT_COMMAND = "***Error:This is not a command.";
const string COMMAND_ERROR = "***Error:Command Error";
const string COMMAND_ISVALID = "isValid";
const string COMMAND_QUIT = "command_quit";

Editor::Editor(const string& input,const string& output) {
	/*
	constructor with input and output files
	*/
	text = list<string>();
	current = text.begin();
	inserting = true;
	currentLineNumber = -1; //text is empty
	this->in = input;
	this->out = output;
	infile.open(in, ios_base::in); //open the input file

	if (in != "") {
		if (infile.fail()) cout << "***Error:The file does not exist!" << endl;
		else { //read the contents in the input file into text
			string temp;
			while (!infile.eof()) {
				infile >> temp;
				currentLineNumber++;
				text.insert(current, temp);
			}
			infile.close();
			}
	}
}

bool Editor::run_command() {
	/*
	读取用户命令，并把命令传给调用的函数
	*/
	string line;
	do {
		cout << PROMPT << endl;
		getline(cin, line);
	} while (parse(line) != COMMAND_QUIT); //exit when line = $quit
	return true;
}

string Editor::parse(const string& line) {
	/*
	判断字符串是否符合命令格式，是否为Quit命令，若是，返回false
	*/
	string s = line;
	//check if it is a command
	if (s[0] != '$') { 
		//check if it is inserting
		if (inserting) { //if so, insert line
			insert_command(line);
			return COMMAND_ISVALID;
		} else { //if not, invalid
			cout << NOT_COMMAND << endl;
			return NOT_COMMAND;
		}
	} else {
		int len = s.length();
		for (int i = 1; i < len; i++) s[i] = tolower(s[i]); //convert the command to lower case

		switch(s[1]) { //determine which command it is
		case 'i': 
			{
				if (s != "$insert") {
					cout << NOT_COMMAND << endl;
					return NOT_COMMAND;
				}
				//s == $insert
				inserting = true;
				return COMMAND_ISVALID;
			}
			break;
		case 'd':
			{
				if (s.substr(0,8) == "$delete ") {
					int a[2]; //to store the first and second line number
					string str = s.substr(8, s.length() - 8);
					string res = command_check(s); //check if the command is valid
					if (res != COMMAND_ISVALID) { //if not, output the error information
						cout << res << endl;
						return res;
					}
					else if (str_to_int(str, a, 2)) {
						delete_command(a[0], a[1]);
						inserting = false;
						return COMMAND_ISVALID;
					} else { //str_to_int(str, a, 2) = false
						cout << COMMAND_ERROR << endl;
						return COMMAND_ERROR;
					}

				} else if (s == "$done") {
					//check if the text is empty
					if (text.size() != 0) //if not, execute done_command
						done_command();
					//if so, print an empty line	
					else cout << endl;
					inserting = false;
					return COMMAND_ISVALID;
				} else {
					cout << NOT_COMMAND << endl;
					return NOT_COMMAND;
				}
			} break;

		case 'l':
			{
				if (s.substr(0,6) == "$line ") {
					if (s[6] == '-' && s[7] == '1' && s.length() == 8) { //case -1
						line_command(-1);
						return COMMAND_ISVALID;
					}
					int m[1]; //to store the line number
					string str = s.substr(6, s.length() - 6);
					string res = command_check(s); //check if the command is valid
					if (res != COMMAND_ISVALID) { //if not, output the error information
						cout << res << endl;
						return res;
					}
					else if (str_to_int(str, m, 1)) {
						line_command(m[0]);
						return COMMAND_ISVALID;
					} else { //str_to_int(str, m, 1) = false
						cout << COMMAND_ERROR << endl;
						return COMMAND_ERROR;
					}
				} else {
					cout << NOT_COMMAND << endl;
					return NOT_COMMAND;
				}
			} break;

		case 'p':
			{
				if (s.substr(0,7) == "$print ") {//命令$print
					int a[2]; //to store the first and second line number
					string str = s.substr(7, s.length() - 7);
					string res = command_check(s); //check if the command is valid
					if (res != COMMAND_ISVALID) { //if not, output the error information
						cout << res << endl;
						return res;
					}
					else if (str_to_int(str, a, 2)) {
						print_line(a[0], a[1]);
						inserting = false;
						return COMMAND_ISVALID;
					} else { ////str_to_int(str, a, 2) = false
						cout << COMMAND_ERROR << endl;
						return COMMAND_ERROR;
					}
				} else {
					cout << NOT_COMMAND << endl;
					return NOT_COMMAND;
				}
			} break;

		case 'q':
			{
				if (s == "$quit") {
					quit();
					inserting = false;
					return COMMAND_QUIT;
				} else {
					cout << NOT_COMMAND << endl;
					return NOT_COMMAND;
				}
			} break;

		case 'o':
			{
				if (s == "$open") {
					open();
					return COMMAND_ISVALID;
				} else {
					cout << NOT_COMMAND << endl;
					return NOT_COMMAND;
				}
			} break;

		case 's':
			{
				if (s == "$save") {
					save();
					return COMMAND_ISVALID;
				} else {
					cout << NOT_COMMAND << endl;
					return NOT_COMMAND;
				}
			} break;

		default: //default case: invalid
			{
				cout << NOT_COMMAND << endl;
				return NOT_COMMAND;
			} break;
		}
	}
}

bool Editor::str_to_int(string s, int a[], int n) {
	/*
	将s中的数字提取出来放到a[]中，n为数字的个数，如果含有非数字的字符，返回false
	*/
	int len = s.length();
	int i = 0, j = 0, count = 0;
	for (;j < n && i < len; j++) {
		count++; //count the number
		a[j] = 0;
		while (s[i] != ' ' && i < len) { //compute each number seperated by space
			if (!isdigit(s[i])) return false;
			a[j] = a[j] * 10 + (s[i] - '0');
			i++;
		}
		i++;
	}
	if (count != n) return false;
	//count = n
	return true;
}

string Editor::command_check(const string& line) { //check if the command is valid
	if (line[2] == 'i') {//命令为$line
		int m;
		int len = line.length() - 6;
		string str = line.substr(6, len);
		int i = 0, count = 0;
		for (; i < len; i++) {
			count++; //count the number
			m = 0;
			while (str[i] != ' ' && i < len) {
				if (!isdigit(str[i])) 
					return "***Error:The command is not followed by a nonnegative integer.";
				//isdigit(str[i]) = true
				m = m * 10 + (str[i] - '0');
				i++;
			}
		}
		if (count != 1) 
			return "***Error:The command is not followed by exactly one integer.";
		else if (m > text.size() - 1) 
			return "***Error:The line number is > the last line number.";
		// count = 1 && m < text.size()
		return COMMAND_ISVALID;

	}else if (line[2] == 'e'|| line[2] == 'r') {//命令为$delete或$print
		int ans = 0;
		if (line[2] == 'e') ans = 8;
		//line[2] == 'r'
		else ans = 7;
		int a[2];
		int len = line.length() - ans; //length starting from number
		string str = line.substr(ans, len);
		int i = 0, j = 0, count = 0;
		for (; j < 2 && i < len; j++) {
			count++; //count the number
			a[j] = 0;
			while (str[i] != ' ' && i < len) {
				if (!isdigit(str[i])) 
					return "***Error:The command is not followed by two nonnegative integers.";
				//isdigit(str[i]) = true
				a[j] = a[j] * 10 + (str[i] - '0');
				i++;
			}
			i++;
		}

		if (count != 2) return "***Error:The command is not followed by two nonnegative integers.";
		else if (a[0] > a[1]) return "***Error:The first line number > the second.";
		else if (a[1] > text.size()-1) return "***Error:The second line number > the last line number.";
		return COMMAND_ISVALID;
	}
	return NOT_COMMAND;
}

void Editor::insert_command(const string& line) {	
	currentLineNumber++;
	text.insert(current, line);
}

void Editor::delete_command(int k, int m) {
	/*
	删除第k行到第m行
	*/
	list<string>::iterator po2 = text.begin();
	list<string>::iterator po3 = text.begin();
	
	for (int l = 0; l < k; l++) po2++; //refer to the position of k
	for (int l = 0; l < m; l++) po3++; //refer to the position of m
	list<string>::iterator p1 = po2;
	p1 = text.erase(po2, po3); //delete from position k to m-1 if k != m

	if (k != m)
		p1 = text.erase(po3);
	
	if (k > 0 && currentLineNumber >= k && currentLineNumber <= m) { //current line is in the lines to delete and k > 0
		current = p1;
		currentLineNumber -= (m-k);
	} else if (k == 0 && currentLineNumber >= k && currentLineNumber <= m) { //current line is in the lines to delete and k = 0
		currentLineNumber = -1;
		current = text.begin();
	} else { //current line is not in the lines to delete
		currentLineNumber -= (m-k)+1;
	}
}

void Editor::done_command() {
	/*
	打印文本
	*/
	cout << "Here is the final text:" << endl << endl;
	if (text.size() != 0) 
		print_line(0, text.size()-1);

}

void Editor::line_command(int m) {
	list<string>::iterator p = text.begin();
	for (int i = 0; i < m && p != text.end(); i++) {p++;};
	current = ++p;
	currentLineNumber = m;
	if (m == -1) {
		current = text.begin();
		currentLineNumber = -1;
	}
	inserting = false;
}

void Editor::print_line(int start, int end) {
	list<string>::iterator p = text.begin();
	list<string>::iterator p2 = text.begin();
	for (int i = 0; i < start; i++) p++; //refer to the start position
	for (int i = 0; i < end; i++) p2++; //refer to the end position

	int count = 0;
	while(1) {
		if ( count++  == currentLineNumber - start) cout << ">"; //print > before current line
		cout << *p << endl;
		if (p != p2) p++;
		//p = p2
		else break;
	}
	
	return ;
}

void Editor::quit() {//退出
	return;
}

void Editor::save() {//将文本存盘
	
	if (out == "") {
		cout << "Are you sure to save all the text to the file:(Y/N) " << endl;
		char c;
		cin >> c; //input answer
		if (tolower(c) == 'y') { //save
			cout << "Please enter the file name: " << endl;
			string file;
			cin >> file;
			out = file;
			outfile.open(file);
			if (outfile.fail()) {
				out = "";
				cout << "***Error:The file does not exist!" << endl;
			} else {
				list<string>::iterator pp = text.begin();
				while (pp != text.end()) {
					outfile << *pp << endl;
					pp++;
				}
				outfile.close();
				cin.get();
			}
		} 
	}
	else {
		cout << "Are you sure to save all the text to the file:(Y/N) " << endl;
		char c;
		cin >> c; //input answer
		if (tolower(c) == 'y') { //save
			outfile.open(out);
			if (outfile.fail()) {
				cout << "***Error:The file does not exist!" << endl;
			} else {
				list<string>::iterator p = text.begin();
				while (p != text.end()) {
					outfile << *p << endl;
					p++;
				}
				outfile.close();
				cin.get();
			}
		}
	}
}

	
void Editor::open() {//打开一个新文件
	cout << "Are you sure to open a text file:(Y/N) " << endl;
	char c;
	if (cin >> c && tolower(c) == 'y') { //input answer y
		string file;
		if (in == "") {
			cout << "Please enter the file name: " << endl;
			cin >> file;
			in = file;
		}
		cout << "Would you like to add contents to edit texts or quit and open a new file? (Add/Open)" << endl;
		string ans;
		cin >> ans; //input answer
		
		if (tolower(ans[0]) == 'a') {
			if (ans[1] == 'd' && ans[2] == 'd') { //add
				infile.open(in);
				if (infile.fail()) {
					cout << "***Error:The file does not exist!" << endl;
				}
				else {
					string temp;
					while(getline(infile, temp)) {//读取本地文件的内容，添加到list
						currentLineNumber++;
						text.insert(current, temp);
					}
					infile.close();
					cin.get();
				}
			} else {
				cout << NOT_COMMAND << endl;
				return;
			}
		} else if (tolower(ans[0] == 'o')){
			if (ans[1] == 'p' && ans[2] == 'e' && ans[3] == 'n') { //open
				currentLineNumber = -1;
				text.clear();
				current = text.begin();
				inserting = true;

				infile.open(in);
				if (infile.fail()) {
					cout << "***Error:The file does not exist!" << endl;
				}
				else {
					string temp;
					while(getline(infile, temp)) {//读取本地文件的内容，添加到list
						currentLineNumber++;
						text.insert(current, temp);
					}
					infile.close();
					cin.get();
				}
			} else {
				cout << NOT_COMMAND << endl;
			}
		} else {
			cout << NOT_COMMAND << endl;
		}
	}
}





