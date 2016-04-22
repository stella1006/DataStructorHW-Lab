#include <iostream>
#include <list>
using namespace std;

list<int> divide_from(list<int> &head) { //divide the list into two parts of equal length
	list<int> second; //second part
	int size = head.size();
	for (int i = size - 1; i >= size / 2; i --) { //traverse the second part from the end
		second.push_front(head.back()); //push the last element of head into second from the beginning
		head.pop_back(); //pop the last element of head
	}

	return second; //first part will also be returned by reference
}

list<int> merge(list<int> first, list<int> second) { //combine first and second lists in order
	list<int>::iterator it = first.end();
	first.splice(it, second); //append the second list to the end of the first list
	first.sort(); //sort the overall list

	return first;
}

void mergesort(list<int> &head) { //merge and sort the list
	if (head.size() > 1) { //base case: head contains 1 or 0 element
		list<int> second_half = divide_from(head); //divide the head into head and second_half
		mergesort(head); //recursive
		mergesort(second_half); //recursive
		head = merge(head, second_half); //combine the head and second_half to form a new head
	}
}

int main() {
	list<int> a;
	for (int i = 0; i < 5; i ++) {
		int n;
		cin >> n;
		a.push_back(n);
	}
	mergesort(a);
	list<int>::iterator i = a.begin();
	for (; i != a.end(); i ++)
		cout << *i << endl;

	system("pause");
	return 0;
}
//8 9 4 5 7