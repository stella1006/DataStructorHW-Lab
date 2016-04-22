#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;


class Customer {
public:
	Customer();
	Customer(int id, int start_time);
	void setIsSer();
	bool getIsSer();
	void setEndWaitingTime(int t);
	void setServing(int t);
	int getID();
	int getEndWaitingTime();
	int getEndServingTime();
	int Customer::getServingTime();
	int Customer::getWaitingTime();
	Customer & operator= (const Customer & c2);

	friend class Bank;
private:
	int ID;
	bool is_serving;
	int start_waiting;
	int end_waiting;
	int time_waiting;
	int start_serving;
	int end_serving;
	int time_serving;
	
};

#endif CUSTOER_H