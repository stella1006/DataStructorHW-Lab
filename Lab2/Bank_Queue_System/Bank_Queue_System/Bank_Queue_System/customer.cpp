#include "customer.h"
#include <windows.h>
#define unit_serving_time 5

Customer::Customer() {
	this->ID = -1;
	this->start_waiting = 0;
	this->end_waiting = 0;
	this->time_waiting = 0;
	this->start_serving = 0;
	this->end_serving = 0;
	this->time_serving = 0;
	
}

Customer::Customer(int id, int start_time) {
	this->ID = id;
	this->start_waiting = start_time;
}



void Customer::setEndWaitingTime(int t) {
	this->end_waiting = t;
	this->time_waiting = end_waiting - start_waiting;
}

void Customer::setServing(int t) {
	//cout << "mygod " << t << endl;
	srand(time(0));
	this->start_serving = t;
	this->time_serving = (rand() % unit_serving_time) + 1;
	this->end_serving = start_serving + time_serving;
	Sleep(100);
	//cout << "end2  " << start_serving << " " << time_serving << " " << end_serving << endl;
}

int Customer::getServingTime() {
	return this->time_serving;
}

int Customer::getWaitingTime() {
	return this->time_waiting;
}

int Customer::getID() {
	return this->ID;
}

int Customer::getEndWaitingTime() {
	return this->time_waiting;
}

Customer & Customer::operator= (const Customer & c2) {
	this->ID = c2.ID;
	this->start_waiting = c2.start_waiting;
	this->end_waiting = c2.end_waiting;
	this->time_waiting = c2.time_waiting;
	this->start_serving = c2.start_serving;
	this->end_serving = c2.end_serving;
	this->time_serving = c2.time_serving;
	return *this;
}

int Customer::getEndServingTime() {
	return this->end_serving;
}


