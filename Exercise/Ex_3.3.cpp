// Problem#: 5212
// Submission#: 4512354
// The source code is licensed under Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
// URI: http://creativecommons.org/licenses/by-nc-sa/3.0/
// All Copyright reserved by Informatic Lab of Sun Yat-sen University
//后最表达式

#include <stdio.h>
#include <string>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <vector>
#include <cassert>
#include <list>
#include <stack>
#include <iomanip>
using namespace std;

int ltoi(char a) {
    return a - 'a' + 1;
}


int main() {
    int n;
    cin >> n;
    while (n--) {
        stack<double> r;
        string s;
        cin >> s;
        double result;
        char c;
        for (int i = 0; i < s.length(); i++) {
            c = s[i];
            if (c >= 'a' && c <= 'z') {
                r.push(ltoi(c));
            } else if (c == '-') {
                double a = r.top();
                r.pop();
                double b = r.top();
                r.pop();
                double c = b - a;
                r.push(c);
            } else if (c == '+') {
                double a = r.top();
                r.pop();
                double b = r.top();
                r.pop();
                double c = b + a;
                r.push(c);
            } else if (c == '*') {
                double a = r.top();
                r.pop();
                double b = r.top();
                r.pop();
                double c = 1.0 * b * a;
                r.push(c);
            } else {
                double a = r.top();
                r.pop();
                double b = r.top();
                r.pop();
                double c = 1.0 * b / a;
                r.push(c);
            }

            
        }
        result = r.top(); 
        cout << setprecision(2) << std::fixed <<  result << endl;

        

    }

    
    
    

    //system("pause");
    return 0;
}                                 
