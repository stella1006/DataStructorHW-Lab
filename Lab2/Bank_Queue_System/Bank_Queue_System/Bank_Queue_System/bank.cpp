#include "bank.h"
#include "customer.h"
#include <windows.h>
#include <string>
//���캯��
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

bool Bank::addServeCustomers(int start_serve_time) {//ɨ��1-5�������޹˿ͣ�û�оͽ�waiting�еĹ˿��Ƴ�����
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

void Bank::serveEnd(int end_time) {//ɨ���Ƿ��й˿ʹ�����ҵ�������򽫹˿�����served���У�����������һ���˿�
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


int Bank::getServingID(int x) {//��ȡÿ���������ڰ���ҵ��Ĺ˿ͺ�
	return serving[x].getID();
}

void Bank::showCusWaitingTime(vector<Customer> &V) {//��ʾÿ���˿͵õ�����֮ǰ�ȴ�ʱ�䵥λ��
	for (int i = 0; i < num_served; i++) {
		if (V[i].getID() != -1)
			cout << V[i].getID() << ": " << V[i].getWaitingTime() << endl;
	}
}

double Bank::getAve() {//��ȡ�˿͵ȴ���ƽ��ʱ����
	double sum = 0;
	double res = 0;
	for (int i = 0; i < num_served; i++) {
		sum += is_served[i].getWaitingTime();
	}
	if (num_served != 0)
		res = 1.0 * sum / is_served.size();
	return res;
}

void Bank::display() {//��ʾʵʱ��Ϣ��ͳ����Ϣ
	cout << "ÿ���������ڰ���ҵ��Ĺ˿�˳��ţ�" << endl;
	for (int i = 0; i < 5; i++) {
		if (serving[i].getID() != -1)
			cout << i + 1 << "�Ŵ��ڣ�" << serving[i].getID() << endl;
		else 
			cout << i+1 << "�Ŵ��ڣ�" << "none" << endl; 
	}
	cout << "Ŀǰ�ȴ��˿�������" << waiting_num_Cumstors  << " ��" << endl;
	
}

void Bank::after_display() {
	//cout << "ÿ���˿͵õ�����֮ǰ�ȴ�ʱ�䵥λ����" << endl;
	//showCusWaitingTime(is_served);
	cout << "�˿͵ȴ���ƽ��ʱ������" << getAve() << endl;
	cout << "ÿ�����ڴ���Ĺ˿�����" << endl;
	for (int i = 0; i < 5; i++) {
		cout << i+1 << "�Ŵ��ڣ�" << served[i] << " ��" << endl;
	}
}

