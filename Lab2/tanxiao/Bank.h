#include <iostream>
#include "Customer.h"
#include <queue>
#include <vector>
using namespace std;

class Bank {
public:
	Bank() {
		numOfEachWindow = new int(5);
		for (int i = 0; i < 5; i ++)
			numOfEachWindow[i] = 0;
		totalTime = 0;
		isFull = false;
	}

	void display() {
		for (int i = 0; i < window.size(); i ++)
			cout << "window" << i << ": " << window[i].id << "  waiting time before servicing: " << window[i].qtime() << endl;
		cout << "number of people waiting in line: " << q.size() << endl << endl;
	}

	void enqueue(Customer c) { //a new customer enter the queue
		c.t0 = currentTime();
		if (!isFull) {
			c.t1 = currentTime();
			window.push_back(c);
			numOfEachWindow[c.id] ++;
		}
		else
			q.push(c);
		if (window.size() == 5)
			isFull = true;
	}

	void getService() {
		for (int i = 0; i < window.size(); i ++) {
			if (currentTime() - window[i].t1 >= window[i].stime) {
				if (q.size() == 0) {
					window[i].id = -1;
					isFull = false;
				}
				else {
					window[i] = q.front();
					q.pop();
					window[i].t1 = currentTime();
					totalTime += window[i].qtime();
				}
				numOfEachWindow[i] ++;
			}
		}
	}

	int currentTime() {
		clock_t t = clock();
		return ((int)t) / CLOCKS_PER_SEC;
	}

	bool isEmpty() { //all windows are empty
		for (int i = 0; i < 5; i ++)
			if (window[i].id != -1)
				return false;
		
		return true;
	}

	queue<Customer> q;
	vector<Customer> window;
	int* numOfEachWindow;
	int totalTime; //total queueing time
	bool isFull; //if all windows are full
};