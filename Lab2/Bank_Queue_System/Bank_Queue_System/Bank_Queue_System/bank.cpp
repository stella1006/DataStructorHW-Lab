#include "bank.h"
#include "customer.h"
#include <windows.h>
#include <string>
//构造函数
Bank::Bank(int maxNumber) {
	is_served.clear();
	memset(served,0,sizeof(served));
	while (!waiting.empty()) waiting.pop();
	Customer blank;
	for (int i = 0; i < 5; i++) serving[i] = blank;
	num_Customers = 0;
	waiting_num_Cumstors = 0;
	ave_wait = 0;
	num_served = 0;
	maxNum = maxNumber;
}

bool Bank::addWaitCustomers(int n, int start_wait_time) {
	cout << "add: " << n << endl;
	for (int i = 0; i < n; i++) {
		if (num_Customers > maxNum) return false;
		else {
			waiting_num_Cumstors++;
			Customer temp(++num_Customers, start_wait_time);
			temp.setServing(0);
			temp.setEndWaitingTime(0);
			waiting.push(temp);
		}
	}
	return true;
}

bool Bank::addServeCustomers(int start_serve_time) {//扫描1-5窗口有无顾客，没有就将waiting中的顾客推出队列
	bool add = false;
	for (int i = 0; i < 5; i++) {
		if (getServingID(i) == -1 && !waiting.empty()) {
			waiting.front().setEndWaitingTime(start_serve_time);
			waiting.front().setServing(start_serve_time);
			Customer temp = waiting.front();
			waiting.pop();
			serving[i] = temp;
			waiting_num_Cumstors--;
			add = true;
		}
	}
	return add;
}

void Bank::serveEnd(int end_time) {//扫描是否有顾客处理完业务，若有则将顾客移至served队列，继续安排下一个顾客
	for (int i = 0; i < 5; i++) {
		if (end_time == serving[i].getEndServingTime()) {
			Customer blank;
			is_served.push_back(serving[i]);
			num_served++;
			served[i]++;
			serving[i] = blank;
		}
	}
}


int Bank::getServingID(int x) {//获取每个窗口正在办理业务的顾客号
	return serving[x].getID();
}

void Bank::showCusWaitingTime(vector<Customer> &V) {//显示每个顾客得到服务之前等待时间单位数
	for (int i = 0; i < num_served; i++) {
		if (V[i].getID() != -1)
			cout << V[i].getID() << ": " << V[i].getWaitingTime() << endl;
	}
}

double Bank::getAve() {//获取顾客等待的平均时间数
	double sum = 0;
	double res = 0;
	for (int i = 0; i < num_served; i++) {
		sum += is_served[i].getWaitingTime();
	}
	if (num_served != 0)
		res = 1.0 * sum / is_served.size();
	return res;
}

void Bank::display() {//显示实时信息和统计信息
	cout << "每个窗口正在办理业务的顾客顺序号：" << endl;
	for (int i = 0; i < 5; i++) {
		if (serving[i].getID() != -1)
			cout << i + 1 << "号窗口：" << serving[i].getID() << endl;
		else 
			cout << i+1 << "号窗口：" << "none" << endl; 
	}
	cout << "目前等待顾客人数：" << waiting_num_Cumstors  << " 人" << endl;
	
}

void Bank::after_display() {
	//cout << "每个顾客得到服务之前等待时间单位数：" << endl;
	//showCusWaitingTime(is_served);
	cout << "顾客等待的平均时间数：" << getAve() << endl;
	cout << "每个窗口处理的顾客数：" << endl;
	for (int i = 0; i < 5; i++) {
		cout << i+1 << "号窗口：" << served[i] << " 人" << endl;
	}
}

