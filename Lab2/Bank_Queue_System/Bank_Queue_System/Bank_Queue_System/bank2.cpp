#include "bank2.h"
#include "customer.h"
#include <windows.h>
#include <string>

Bank2::Bank2() {
	for (int i = 0; i < 5; i++) is_served[i].clear();
	memset(windows,0,sizeof(windows));
	memset(wait,0,sizeof(wait));
	memset(num_served,0,sizeof(num_served));
	memset(ave_wait,0,sizeof(ave_wait));
	num_Customers = 0;
	ser = new queue<Customer>[5];
	Customer blank;
	for (int i = 0; i < 5; i++) {
		serving[i] = blank;
	}
}

Bank2::~Bank2() {
	for (int i = 0; i < 5; i++) is_served[i].clear();
	delete ser;
}

int Bank2::findShort(int d[], int n) {
	int index = 0;
	int min = d[0];
	for (int i = 1; i < n; i++) {
		if (d[i] < min) {
			min = d[i];
			index = i;
		}
	}
	return index;
}

int Bank2::getServingID(int x) {//��ȡÿ���������ڰ���ҵ��Ĺ˿ͺ�
	return serving[x].getID();
}

void Bank2::addWait(int n, int start_wait_time) {
	cout << "add: " << n << endl;
	int s = findShort(wait, 5);
	for (int i = 0; i < n; i++) {
		Customer temp(++num_Customers, start_wait_time);
		temp.setServing(0);
		temp.setEndWaitingTime(0);
		(ser[s]).push(temp);
		windows[s]++;
		wait[s]++;
		s = findShort(wait, 5);
	}
}

void Bank2::addSer(int start_serve_time) {
	for (int i = 0; i < 5; i++) {
		if (!ser[i].empty() && getServingID(i) == -1) {
			
			this->ser[i].front().setServing(start_serve_time);
			this->ser[i].front().setEndWaitingTime(start_serve_time);	
			//wait[i]--;
			serving[i] = ser[i].front();
		}
	}
}

void Bank2::serEnd(int end_time) {
	for (int i = 0; i < 5; i++) {
		if (!ser[i].empty()) {
			if (ser[i].front().getEndServingTime() == end_time) {
				is_served[i].push_back(ser[i].front());
				ser[i].pop();
				num_served[i]++;
				Customer blank;
				serving[i] = blank;
				wait[i]--;
			}
		}
	}
}

void Bank2::showCusWaitingTime(vector<Customer> q[]) {//ÿ���˿͵õ�����֮ǰ�ȴ�ʱ�䵥λ��
	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < q[j].size(); i++) {
			cout << q[j][i].getID() << ": " << q[j][i].getEndWaitingTime() << endl;
		}
	}
}

double Bank2::getAve(int q) {//��ȡ�˿͵ȴ���ƽ��ʱ����
	double sum = 0;
	double res = 0;
	for (int i = 0; i < num_served[q]; i++) {
		sum += is_served[q][i].getWaitingTime();
	}
	if (num_served != 0)
		res = 1.0 * sum / is_served[q].size();
	return res;
}

void Bank2::display() {//��ʾʵʱ��Ϣ��ͳ����Ϣ
	cout << "ÿ���������ڰ���ҵ��Ĺ˿�˳��ţ�" << endl;
	for (int i = 0; i < 5; i++) {
		if (serving[i].getID() != -1) 
			cout << i+1 << "�Ŵ��ڣ�" << serving[i].getID() << endl;
		else 
			cout << i+1 << "�Ŵ��ڣ�" << "none" << endl; 
		cout  << "�ȴ��˿�������" << wait[i]  << " ��" << endl;
	}
}

void Bank2::after_display() {
	//cout << "ÿ���˿͵õ�����֮ǰ�ȴ�ʱ�䵥λ����" << endl;
	//showCusWaitingTime(is_served);
	for (int i = 0; i < 5; i++)
		cout << i+1 << "�Ŵ��ڹ˿͵ȴ���ƽ��ʱ������" << getAve(i) << endl;
	cout << "ÿ�����ڴ���Ĺ˿�����" << endl;
	for (int i = 0; i < 5; i++) {
		cout << i+1 << "�Ŵ��ڣ�" << num_served[i] << " ��" << endl;
	}
}

