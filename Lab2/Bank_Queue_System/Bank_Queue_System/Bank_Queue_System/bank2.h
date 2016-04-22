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
	void showCusWaitingTime(vector<Customer> []);//ÿ���˿͵õ�����֮ǰ�ȴ�ʱ�䵥λ��
	double getAve(int);//��ȡ�˿͵ȴ���ƽ��ʱ����
	int getServingID(int);//��ȡÿ���������ڰ���ҵ��Ĺ˿ͺ�

	int findShort(int cc[], int n);//ɨ��������ڣ����صȴ��������ٵĴ���
	void addWait(int n, int start_wait_time);
	void addSer(int start_serve_time);
	void serEnd(int end_time);//ɨ���Ƿ��й˿ʹ�����ҵ�������򽫹˿�����served���У�����������һ���˿�
	void display();//��ʾʵʱ��Ϣ��ͳ����Ϣ
	void after_display();

private:
	//queue<Customer> waiting;//�����ŶӵĹ˿�
	vector<Customer> is_served[5];//�Ѿ�����Ĺ˿�;
	int windows[5];//5�������ܹ˿���=�ѷ���ĺ������Ŷӵ�
	int wait[5];//5���������ڵȴ��Ĺ˿���
	int num_served[5];//5�������Ѿ�������Ĺ˿���
	double ave_wait[5];//5�����ڹ˿͵ȴ���ƽ����	
	int num_Customers;//�ܹ˿���
	queue<Customer> *ser;//5�����ڵĶ���
	Customer serving[5];//5���������ڰ���ҵ��Ĺ˿ͺ�
};

#endif BANK2_H