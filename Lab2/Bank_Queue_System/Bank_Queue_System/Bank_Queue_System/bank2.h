#ifndef BANK2_H
#define BANK2_H

#include <queue>
#include <vector>
#include <iostream>
#include <map>
#include "customer.h"
using namespace std;

class Bank2: Customer{
	
public:
	Bank2();//
	~Bank2();
	void showCusWaitingTime(vector<Customer> []);//每个顾客得到服务之前等待时间单位数
	double getAve(int);//获取顾客等待的平均时间数
	int getServingID(int);//获取每个窗口正在办理业务的顾客号

	int findShort(int cc[], int n);//扫描五个窗口，返回等待人数最少的窗口
	void addWait(int n, int start_wait_time);
	void addSer(int start_serve_time);
	void serEnd(int end_time);//扫描是否有顾客处理完业务，若有则将顾客移至served队列，继续安排下一个顾客
	void display();//显示实时信息和统计信息
	void after_display();

private:
	//queue<Customer> waiting;//正在排队的顾客
	vector<Customer> is_served[5];//已经服务的顾客;
	int windows[5];//5个窗口总顾客数=已服务的和正在排队的
	int wait[5];//5个窗口正在等待的顾客数
	int num_served[5];//5个窗口已经处理完的顾客数
	double ave_wait[5];//5个窗口顾客等待的平均数	
	int num_Customers;//总顾客数
	queue<Customer> *ser;//5个窗口的队列
	Customer serving[5];//5个窗口正在办理业务的顾客号
};

#endif BANK2_H