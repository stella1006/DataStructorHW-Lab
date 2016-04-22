#ifndef BANK_H
#define BANK_H

#include <queue>
#include <vector>
#include <iostream>
#include <map>
#include "customer.h"
using namespace std;

class Bank: Customer{
public:
	Bank(int maxNumber);//参数为最大服务数量
	int getServingID(int);//获取每个窗口正在办理业务的顾客号
	void showCusWaitingTime(vector<Customer> &);//每个顾客得到服务之前等待时间单位数
	double getAve();//获取顾客等待的平均时间数

	bool addWaitCustomers(int n, int start_wait_time);
	bool addServeCustomers(int start_serve_time);
	void serveEnd(int end_time);//扫描是否有顾客处理完业务，若有则将顾客移至served队列，继续安排下一个顾客
	void display();//显示实时信息和统计信息
	void after_display();
private:
	queue<Customer> waiting;//正在排队的顾客
	vector<Customer> is_served;//已经服务的顾客;
	Customer serving[5];//5个窗口正在办理业务的顾客号
	int num_Customers;//总顾客数
	int waiting_num_Cumstors;//正在等待的顾客数
	int num_served;//已经处理完的顾客数
	double ave_wait;//顾客等待的平均数
	int maxNum;//最大服务数量	
	int served[5];
};

#endif BANK_H