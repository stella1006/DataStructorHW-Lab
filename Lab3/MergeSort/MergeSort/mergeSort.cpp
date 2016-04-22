#include "linkedlist.h"
#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <algorithm>
#include <set>
#include <map>
#include <list>
#include <windows.h>
using namespace std;

template <typename T>
//merge and sort the list
void mergesort(LinkedList<T> &head) {//merge and sort the list
	if (head.size() > 1) { //base case: head contains 1 or 0 element
		LinkedList<T> res1, res2;
		LinkedList<T> second_half = divide_from(head, res1);//divide the head into head and second_half
		mergesort(head);//recursive
		mergesort(second_half);//recursive
		head = merge(head, second_half, res2);//combine the head and second_half to form a new head
	} 
}

template <typename T>
//devide the list into two parts from the middle, return the second part
LinkedList<T>& divide_from(LinkedList<T> &head, LinkedList<T> &res) {
	
	LinkedList<T>::Node* slow = head.getStart();
	LinkedList<T>::Node* fast = head.getStart();
	while (fast != NULL && fast->next != NULL) {//pointer slow move s step while fast move two steps,
		slow = slow->next;                      // when the fast move to the end, the slow will in the middle
		fast = fast->next;
		if (fast == NULL) break;
		fast = fast->next;
	}
	slow = slow->next;
	while (slow != NULL) {           
		res.push_back(slow->data);//reserve the second part of the list
		slow = head.erase(slow);//delete the second part from the origin list
	}
	return res;
}

template <typename T>
//combine first and second lists in order
LinkedList<T>& merge(LinkedList<T> &first, LinkedList<T> &second, LinkedList<T> &res) {
	if (first.empty() || second.empty()) return first.empty() ? first : second;
	LinkedList<T>::Node* s1 = first.getStart()->next;    //get the first element of list one
	LinkedList<T>::Node* s2 = second.getStart()->next;   //get the first element of list two
	while (s1 != NULL && s2 != NULL) {      //when both lists are not empty
		if (s1->data < s2->data) {          //if the value in list one is smaller than that in list two, 
			res.push_back(s1->data);        //add it to the result value, increase the pointer
			s1 = s1->next;
		} else {
			res.push_back(s2->data);       //if the value in list two is smaller than that in list one,
			s2 = s2->next;                 //add it to the result value, increase the pointer
		}
	}
	//if some values are remained in the list, add all them to the reslut
	while (s1 != NULL) {                
		res.push_back(s1->data);
		s1 = s1->next;
	}
	while (s2 != NULL) {
		res.push_back(s2->data);
		s2 = s2->next;
	}
	return res;
}

int main() {
	LinkedList<int> l;
	srand(time(0));
	for (int i = 0; i < 10; i++) {
		l.push_back(rand()%100 + 1); // create a list of random values and sort them
	}
	cout << "Disordered list: " << endl;;
	l.print();      //print the disordered list 
	mergesort(l);
	cout << "Sorted list: " << endl;;
	l.print();      //print the ordered list
	system ("pause");
	return 0;
}
