#pragma once
#include <ctime>
using namespace std;

class Customer {
public:
	Customer() {}

	Customer(int id, int stime) {
		this->id = id;
		this->stime = stime;
	}

	int qtime() { //queueing time
		return t1 - t0;
	}

	int id;
	int t0; //time when entering the queue
	int t1; //time when starting the service
	//int t2; //time when ending the service
	int stime; //servicing time
};