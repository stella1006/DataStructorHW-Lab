#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include "bank.h"
#include "bank2.h"
#include "customer.h"
using namespace std;
#define unit_waiting_time 2
#define add_cus 5
#define maxCus 100
#define maxT 10

int main() {
	//cout << "aa" << endl;
	Bank myBank(maxCus);
	Bank2 mB;
	srand(time(0));
	for (int t = 0; t < maxT; t++) {
		cout << "Time: " << t << endl;
		if (t % unit_waiting_time == 0)
			//第一种服务方法
			/*myBank.addWaitCustomers((rand() % add_cus + 1), t);
			myBank.addServeCustomers(t);
			myBank.serveEnd(t);
			myBank.display();
			if (t  ==  maxT-1)
				myBank.after_display();*/
			//第二种服务方法
			mB.addWait((rand() % add_cus +1), t);
			mB.addSer(t);
			mB.serEnd(t);
			mB.display();
			if (t == maxT - 1)
				mB.after_display();
		//system("cls");
		Sleep(1000);

	}
	
	system ("pause");
	return 0;
}
