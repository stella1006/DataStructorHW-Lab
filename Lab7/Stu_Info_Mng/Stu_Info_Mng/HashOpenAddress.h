#ifndef HASHOPENADDRESS_H
#define HASHOPENADDRESS_H

#include "Student.h"
#include <iostream>
#include <vector>
using namespace std;

template <typename HashObj>
class HashOpen {
public:
	enum EntryType {ACTIVE, EMPTY, DELETED};
	struct HashEntry {
		HashObj element;
		EntryType info;

		HashEntry (const HashObj & e = HashObj(), EntryType i = EMPTY) : element(e), info(i) {}

	};

	explicit HashOpen(int size = 107);
	void findKey(const string & s);
	void makeEmpty();
	void print();
	const vector<HashEntry> & getArray() const{
		return Varray;
	}

	bool contains(const HashObj & x) const;
	bool insert(const HashObj & x);
	bool remove(const HashObj & x);

	
private:
	
	
	vector<HashEntry> Varray;
	int currentSize;

	bool isActive(int currentPos) const;
	int findPos(const HashObj & x) const;
	int hash(const string & key) const;
	int myhash(const HashObj & x) const;
};

template <typename HashObj>
HashOpen<HashObj>::HashOpen(int size = 107) {
	currentSize = 0;
	Varray.resize(size);
	makeEmpty();
}

template <typename HashObj>
void HashOpen<HashObj>::makeEmpty() {
	for (int i = 0; i < Varray.size(); i++) {
		Varray[i].info = EMPTY;
	}
}

template <typename HashObj>
bool HashOpen<HashObj>::isActive(int currentPos) const {
	return Varray[currentPos].info == ACTIVE;
}

template <typename HashObj>
int HashOpen<HashObj>::findPos(const HashObj & x) const {
	int offset = 1;
	int currentPos = myhash(x);
	while (Varray[currentPos].info != EMPTY && Varray[currentPos].element != x) {
		currentPos += offset; //compute its probe
		offset += 2;
		if (currentPos >= Varray.size())
			currentPos -= Varray.size();
	}
	return currentPos;
}

template <typename HashObj>
int HashOpen<HashObj>::hash(const string & ID) const{
	string key = ID.substr(ID.length() - 6, ID.length() - 1);
	int hashval = 0;
	for (int i = 0; i < key.length(); i++) {
		hashval = 10 * hashval + key[i];
	}
	hashval %= Varray.size();
	if (hashval < 0) 
		hashval += Varray.size();
	return hashval;
}

template <typename HashObj>
int HashOpen<HashObj>::myhash(const HashObj & x) const {
	string ID = x.getID();
	int hashval = hash(ID);

	return hashval;
}

template <typename HashObj>
bool HashOpen<HashObj>::contains(const HashObj & x) const {
	return find(Varray.begin(),Varray.end(), x) != Varray.end();
}

template <typename HashObj>
bool HashOpen<HashObj>::insert(const HashObj & x) {
	int currentPos = findPos(x);
	if (isActive(currentPos)) return false;

	Varray[currentPos] = HashEntry(x, ACTIVE);

	if (++currentPos > Varray.size()) {
		cout << "The table is full" << endl;
		return false;
	}
	return true;
}

template <typename HashObj>
bool HashOpen<HashObj>::remove(const HashObj & x) {
	int currentPos = findPos(x);
	if (!isActive(currentPos)) return false;

	Varray[currentPos].info = DELETED;
	return true;
}

template <typename HashObj>
void HashOpen<HashObj>::print() {
	const vector<HashEntry> V = getArray();
	for (int i = 0; i < V.size(); i++) {
		cout << i << " ";
		if (isActive(i)) 
			cout << V[i].element.getName() << endl;
		else cout << endl;
	}
}

template <typename HashObj>
void HashOpen<HashObj>::findKey(const string & s) {
	int offset = 1;
	int currentPos = hash(s);
	while (Varray[currentPos].info != EMPTY && Varray[currentPos].element.getID() != s) {
		currentPos += offset; //compute its probe
		offset += 2;
		if (currentPos >= Varray.size())
			currentPos -= Varray.size();
	}
	if (isActive(currentPos)) {
		HashObj stu = Varray[currentPos].element;
		cout << stu.getID() << " " << stu.getName() << " " << stu.getAge() << " " << (stu.getSex() == 0? "Male":"Female") << endl;
	}
	else {
		cout << s <<" This ID is not contained in the system" << endl;
	}

}


#endif HASHOPENADDRESS_H