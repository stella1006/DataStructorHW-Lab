#ifndef LINKEDLIST_H
#define LINKEDLIST_H

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
template <typename T>
class LinkedList {
public:
	struct Node {
		T data;
		Node *next;
		Node():data(0), next(NULL) {}
		Node (const T & x, Node *p = NULL) :data(x), next(p) {}
	};
	//Motheds of LinkedList
	LinkedList();
	~LinkedList() {clear();};
	LinkedList(const LinkedList &l);//construt a new linkedlist with an origin linkedlist
	LinkedList<T>& operator = (const LinkedList<T> &l);//copy a linkedlist
	int size() const{return theSize;};//return the numbers of elements in the list
	bool empty() const {return (theSize==0);};
	void clear();

	Node* getStart() const {return start;};//if the list is not NULL, return the pointer of the first pointer
	Node* getTail() const{return tail;};//if the list is not NULL, return the pointer of the last pointer
	void push_front(const T &x);//insert x before the first value
	void push_back(const T & element);//insert x to the back
	void print() const;//print the list
	Node* erase(Node* position) {//delete the value of position, return the point of its successor
		Node* st = start;
		while (st->next != NULL) {
			if (st->next == position) {
				st->next = position->next;
				theSize--;
				break;
			}
			st = st->next;
		}
		return position->next;
	}

	//Node* insert(Node* position, const T &x);//insert x int the position, return the pointer that points to inerted values
	//void traverse(void (*visit)(T &));
	//Node* advance(Node* p) {return p->next;};//return the next position of p

private:
	//Node* previous(Node* p);//return the pointer that points to the previous node
	Node* start;//pointer that points to the first node
	Node* tail;//pointer that points to the current node
	int theSize;//count the numbers of the nodes in the list
	//inline void deepCopy(const LinkedList<T> &original);
};

template <typename T>
LinkedList<T>::LinkedList() {//constructor
	start = new Node();
	tail = new Node();
	theSize = 0;
}
template <typename T>
LinkedList<T>::LinkedList(const LinkedList &l) {//construct a new linkedlist with an origin linkedlist
	this->start = new Node();
	this->tail = new Node();
	this->theSize = 0;
	Node* st = l.getStart();
	while (st != NULL && st->next != NULL) {
		st = st->next;
		this->push_back(st->data);
	}
}
template <typename T>
LinkedList<T>& LinkedList<T>::operator = (const LinkedList<T> &l) {//overload operator =
	this->start = new Node();
	this->tail = new Node();
	this->theSize = 0;
	Node* st = l.getStart();
	while (st != NULL && st->next != NULL) {
		st = st->next;
		push_back(st->data);	
	}
	return *this;
}

template <typename T>
void LinkedList<T>::clear() {//clear all the data and release the momory
	while(start != NULL) {
		tail = start;
		start = start->next;
		delete tail;
	}
	tail = NULL;
}

template <typename T>
void LinkedList<T>::push_front(const T &x){//insert x before the first value
	Node *NNode = new Node();
	NNode->data = element;
	NNode->next = start;
	start = NNode;
	theSize++;
}

template <typename T>
void LinkedList<T>::push_back(const T & element) {//insert x to the back
	Node *NNode = new Node();
	NNode->data = element;
	NNode->next = NULL;
	//T item;
	if(start == NULL) {//if the list is empty, insert direatly
		start = NNode;
		tail = NNode;
		theSize++;
		return;
	}
	Node* temp = start;
	while(temp != NULL && temp->next != NULL){
		temp = temp->next;
	}
	temp->next = NNode;
	theSize++;
	tail = NNode;
}


template <typename T>
void LinkedList<T>::print() const{
	if (start == NULL) {
		cout << "NULL" << endl;
		return;
	}
	Node* t = start->next;
	while (t!= NULL) {
		cout << t->data << " ";
		t = t->next;
	}
	cout << endl;
}

#endif LINKEDLIST_H

