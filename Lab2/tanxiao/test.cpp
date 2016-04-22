#include "Bank.h"
#include "Customer.h"
#include <Windows.h>
using namespace std;

int main() {
	Bank b;
	srand(time(0));
	int count = 0;
	do {
		if (b.currentTime() <= 30) { //after 60s no one come in
			int num = (rand() % 5) + 1; //1-5 customers per unit
			for (int i = 0; i < num; i ++) {
				int stime = rand() % 5 + 1; //1-5s service time
				Customer c(count, stime);
				b.enqueue(c);
				count ++;
			}
		}
		b.display();
		b.getService();
		Sleep(1000);
	} while (!b.q.empty() || !b.isEmpty());
	cout << "average waiting time: " << b.totalTime / count << endl;
	for (int i = 0; i < 5; i ++)
		cout << "window " << i << " has served " << b.numOfEachWindow[i] << " customers" << endl;

	system("pause");
	return 0;
}