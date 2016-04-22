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
	Bank(int maxNumber);//����Ϊ����������
	int getServingID(int);//��ȡÿ���������ڰ���ҵ��Ĺ˿ͺ�
	void showCusWaitingTime(vector<Customer> &);//ÿ���˿͵õ�����֮ǰ�ȴ�ʱ�䵥λ��
	double getAve();//��ȡ�˿͵ȴ���ƽ��ʱ����

	bool addWaitCustomers(int n, int start_wait_time);
	bool addServeCustomers(int start_serve_time);
	void serveEnd(int end_time);//ɨ���Ƿ��й˿ʹ�����ҵ�������򽫹˿�����served���У�����������һ���˿�
	void display();//��ʾʵʱ��Ϣ��ͳ����Ϣ
	void after_display();
private:
	queue<Customer> waiting;//�����ŶӵĹ˿�
	vector<Customer> is_served;//�Ѿ�����Ĺ˿�;
	Customer serving[5];//5���������ڰ���ҵ��Ĺ˿ͺ�
	int num_Customers;//�ܹ˿���
	int waiting_num_Cumstors;//���ڵȴ��Ĺ˿���
	int num_served;//�Ѿ�������Ĺ˿���
	double ave_wait;//�˿͵ȴ���ƽ����
	int maxNum;//����������	
	int served[5];
};

#endif BANK_H