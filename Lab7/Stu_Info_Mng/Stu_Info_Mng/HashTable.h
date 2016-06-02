#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Student.h"
#include <iostream>
#include <vector>
#include <list>
using namespace std;

template <typename HashObj>
class HashTable {
public:
	explicit HashTable(int size = 107);

	void makeEmpty();
	void print();
	const vector<list<HashObj> > & getList() const{
		return VList;
	}

	bool contains(const HashObj & x) const;
	bool insert(const HashObj & x);
	void findKey(const string & s);
	void remove(const HashObj & x);

private:
	vector<list<HashObj> > VList;
	int currentSize;
	int hash(const string & key) const;
	int myhash(const HashObj & x) const;
};

template <typename HashObj>
HashTable<HashObj>::HashTable(int size = 107) {
	currentSize = 0;
	VList.resize(size);
	makeEmpty();
}

template <typename HashObj>
void HashTable<HashObj>::makeEmpty() {
	for (int i = 0; i < VList.size(); i++) {
		VList[i].clear();
	}

}

template <typename HashObj>
int HashTable<HashObj>::hash(const string & ID) const{
	string key = ID.substr(ID.length() - 6, ID.length() - 1);
	int hashval = 0;
	for (int i = 0; i < key.length(); i++) {
		hashval = 10 * hashval + key[i];
	}
	hashval %= VList.size();
	if (hashval < 0) 
		hashval += VList.size();
	return hashval;
}

template <typename HashObj>
void HashTable<HashObj>::print() {
	const vector<list<HashObj> > V = getList();
	for (int i = 0; i < V.size(); i++) {
		list<HashObj> l = V[i];
		if (!l.empty()) {

			cout << i << " ";
			for (list<HashObj>::iterator j = l.begin(); j != l.end(); j++) {
				if ((*j).getName() != "")
					cout << (*j).getName() << " ";
			}
			//if (!V[i].empty()) 
				cout << endl;
		}
	}
}


template <typename HashObj>
int HashTable<HashObj>::myhash(const HashObj & x) const {
	string ID = x.getID();
	int hashval = hash(ID);
	return hashval;
}

template <typename HashObj>
bool HashTable<HashObj>::contains(const HashObj & x) const {
	//int hashval = myhash(x);
	const list<HashObj> &whichList = VList[myhash(x)];
	return find(whichList.begin(), whichList.end(), x) != whichList.end();
}


template <typename HashObj>
bool HashTable<HashObj>::insert(const HashObj & x) {
	list<HashObj> &whichList = VList[myhash(x)];
	if (!contains(x)) {
		whichList.push_back(x);
	}
	if (++currentSize > VList.size()) return false;
	return true;
}

template <typename HashObj>
void HashTable<HashObj>::findKey(const string & s) {
	int hashval = hash(s);
	list<HashObj> &whichList = VList[hashval];
	list<HashObj>::iterator itr = whichList.begin();
	bool isContained = false;
	for ( ; itr != whichList.end(); itr++) {
		if ((*itr).getID() == s) {
			isContained = true;
			cout << (*itr).getID() << " " << (*itr).getName() << " " << (*itr).getAge() << " " << ((*itr).getSex() == 0? "Male":"Female") << endl;
		}
	}
	if (!isContained) cout << s <<" This ID is not contained in the system" << endl;
}

template <typename HashObj>
void HashTable<HashObj>::remove(const HashObj & x) {
	list<HashObj> &whichList = VList[myhash(x)];
	list<HashObj>::iterator itr = find(whichList.begin(), whichList.end(), x);

	if (itr != whichList.end()) {
		whichList.erase(itr);
		--currentSize;
	}
}

#endif HASHTABLE_H