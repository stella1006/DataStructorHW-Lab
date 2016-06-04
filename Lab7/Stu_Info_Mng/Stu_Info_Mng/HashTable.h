#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Student.h"
#include <iostream>
#include <vector>
#include <list>
#include <ctime>
using namespace std;

template <typename HashObj>
class HashTable {
public:
	explicit HashTable(int size = 107);   //constructor

	void makeEmpty();    //set the information of all elements to be EMPTY
	void print();   //print all the information that is stored

	const vector<list<HashObj> > & getList() const{   //get the whole vector that stored the information
		return VList; 
	}

	bool contains(const HashObj & x) const;    //check if the vector contains the object x
	bool insert(const HashObj & x);           //insert the object x
	void findKey(const string & s);           //given key value find its whole information
	void remove(const string & s);           //given key value remove its whole information
	double cal_time(const string & s);        //calculate the time that use to find a key
private:
	vector<list<HashObj> > VList;     //Use vector to store the students' information 
	int hash(const string & key) const;   //given key value find its hash address
	int myhash(const HashObj & x) const;  //given hashObject find its hash address
};

template <typename HashObj>
HashTable<HashObj>::HashTable(int size = 107) {  //constructor
	VList.resize(size);
	makeEmpty();
}

template <typename HashObj>
void HashTable<HashObj>::makeEmpty() {    //clear the contain
	for (int i = 0; i < VList.size(); i++) {
		VList[i].clear();
	}

}

template <typename HashObj>
int HashTable<HashObj>::hash(const string & ID) const{
	string key = ID.substr(ID.length() - 6);    //according to the last 6 ID numbers, calculate the hash address
	int hashval = 0;
	for (int i = 0; i < key.length(); i++) {
		hashval = 10 * hashval + key[i];  //calculate the hash address
	}
	hashval %= VList.size();    
	if (hashval < 0) 
		hashval += VList.size();
	return hashval;
}

template <typename HashObj>
void HashTable<HashObj>::print() {    //print all the information that is stored
	const vector<list<HashObj> > V = getList();
	for (int i = 0; i < V.size(); i++) {
		list<HashObj> l = V[i];
		if (!l.empty()) {

			cout << i << " ";
			for (list<HashObj>::iterator j = l.begin(); j != l.end(); j++) {
				if ((*j).getName() != "")
					cout << (*j).getName() << " ";
			}
				cout << endl;
		}
	}
}


template <typename HashObj>
int HashTable<HashObj>::myhash(const HashObj & x) const {   //given hashObject find its hash address
	string ID = x.getID();   //get the ID from hash object
	int hashval = hash(ID);   //find its hash address
	return hashval;
}

template <typename HashObj>
bool HashTable<HashObj>::contains(const HashObj & x) const {  
	const list<HashObj> &whichList = VList[myhash(x)];   //get the list according to coressponding hash address of the object x
	return (find(whichList.begin(), whichList.end(), x) != whichList.end());
}


template <typename HashObj>
bool HashTable<HashObj>::insert(const HashObj & x) {
	list<HashObj> &whichList = VList[myhash(x)];    //get the list according to coressponding hash address of the object x
	if (!contains(x)) {    //if it isn't stored, store it
		whichList.push_back(x);
	} else return false;
	return true;
}

template <typename HashObj>
void HashTable<HashObj>::findKey(const string & s) {
	int hashval = hash(s);    //find hash address of s
	list<HashObj> &whichList = VList[hashval];  //get the list according to coressponding hash address of s
	list<HashObj>::iterator itr = whichList.begin();
	bool isContained = false;
	for ( ; itr != whichList.end(); itr++) {  //traverse the corresponding list
		if ((*itr).getID() == s) {
			isContained = true;
			cout << "Found successfully: " << endl;  //print the information that is found
			cout << "Name: " << (*itr).getName() << endl;
			cout << "ID: " << (*itr).getID() << endl;
			cout << "Age: " << (*itr).getAge() << endl;
			cout << "Gender: " << ((*itr).getSex() == 0? "Male":"Female")  << endl;		}
	}
	if (!isContained) cout << s <<" This ID is not contained in the system" << endl;
}

template <typename HashObj>
double HashTable<HashObj>::cal_time(const string & s) {
	
	DWORD start, end;
	start = timeGetTime();
	int hashval = hash(s);    //find hash address of s
	list<HashObj> &whichList = VList[hashval];  //get the list according to coressponding hash address of s
	list<HashObj>::iterator itr = whichList.begin();
	bool isContained = false;
	for ( ; itr != whichList.end(); itr++) {  //traverse the corresponding list
		if ((*itr).getID() == s) 
			isContained = true;
	}
	if (!isContained) cout << s <<" This ID is not contained in the system" << endl;
	end = timeGetTime();
	return (double)((double)(end - start) / 1000);
}

template <typename HashObj>
void HashTable<HashObj>::remove(const string & s) {
	int hashval = hash(s);
	list<HashObj> &whichList = VList[hashval];
	list<HashObj>::iterator itr = whichList.begin();
	bool isContained = false;
	for ( ; itr != whichList.end(); itr++) {   //traverse the corresponding list
		if ((*itr).getID() == s) {
			isContained = true;
			cout << "\nRemoved successfully: " << endl;  //print the information that is removed
			cout << "Name: " << (*itr).getName() << endl;
			cout << "ID: " << (*itr).getID() << endl;
			cout << "Age: " << (*itr).getAge() << endl;
			cout << "Gender: " << ((*itr).getSex() == 0? "Male":"Female") <<  endl;
			whichList.erase(itr);
			break;
		}
	}
	if (!isContained) cout << s <<" This ID is not contained in the system" << endl;

}

#endif HASHTABLE_H