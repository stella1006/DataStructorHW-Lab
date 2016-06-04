#include <vector>
#include <cmath>
#include <string>
#include <ctime>
using namespace std;

template <typename HashObj> //int id
class HashTable2 {
public:
	explicit HashTable2(int size = 101) { //constructor
		array.resize(nextPrime(size)); //set the array size to be the next prime number after size
		makeEmpty();
	}

	bool contains(const HashObj& x) const { //if the table contains the object x
		return isActive(findPos(x)); //if the position of x is active
	}

	void makeEmpty() {
		currentSize = 0;
		for (int i = 0; i < array.size(); i++) //set the information of all elements to be EMPTY
			array[i].info = EMPTY;
	}

	bool insert(const HashObj& x) { //if succeed, return 1
		int currentPos = findPos(x);
		if (isActive(currentPos)) //x already existed in the table
			return false;
		array[currentPos] = HashEntry(x, ACTIVE); //insert the entry
		if (++currentSize > array.size() / 2) //if current size is larger than half the array size
			rehash(); //enlarge the size of the array
		return true;
	}

	bool remove(const string& x) { //if succeed, return 1
		int currentPos = hash(x); //original position
		while (array[currentPos].info != EMPTY && array[currentPos].element.id != x) { 
		//terminate when the position is found or x already exists in the table
			currentPos += 1; //linear probing
			if (currentPos >= array.size()) //mod operation
				currentPos -= array.size();
		}
		if (isActive(currentPos))
			array[currentPos].info = DELETED; //set the information to be DELETED
		else
			return false;
	}

	void findKey(const string& x) {
		int currentPos = hash(x); //original position
		while (array[currentPos].info != EMPTY && array[currentPos].element.getID() != x) { 
		//terminate when the position is found or x already exists in the table
			currentPos += 1; //linear probing
			if (currentPos >= array.size()) //mod operation
				currentPos -= array.size();
		}
		if (isActive(currentPos)) {
			cout << "Found successfully: " << endl;  //print the information that is found
			cout << "Name: " << array[currentPos].element.getName() << endl;
			cout << "ID: " << array[currentPos].element.getID() << endl;
			cout << "Age: " << array[currentPos].element.getAge() << endl;
			cout << "Gender: " << (array[currentPos].element.getSex() == 0? "Male":"Female")  << endl;		
		}

		else
			cout << "Fail" << endl;
	}

	double cal_time(const string& x) {
		DWORD start, end;
		start = timeGetTime();
		int currentPos = hash(x); //original position
		while (array[currentPos].info != EMPTY && array[currentPos].element.getID() != x) { 
		//terminate when the position is found or x already exists in the table
			currentPos += 1; //linear probing
			if (currentPos >= array.size()) //mod operation
				currentPos -= array.size();
		}

		if (!isActive(currentPos)) cout << "Fail" << endl;
			
		end = timeGetTime();
		//cout << (double)((double)(end - start) / 1000) << endl;
		return (double)((double)(end - start) / 1000);
	}

	enum EntryType {ACTIVE, EMPTY, DELETED}; //three state of entry
	struct HashEntry {
		HashObj element;
		EntryType info;

		HashEntry(const HashObj& e = HashObj(), EntryType i = EMPTY) { //constructor of HashEntry
			element = e;
			info = i;
		}
	};

	vector<HashEntry> &getArray() {
		return array;
	}

	

private:
	

	vector<HashEntry> array;
	int currentSize;

	bool isActive(int currentPos) const { //if the current position is ACTIVE
		return array[currentPos].info == ACTIVE;
	}

	int findPos(const HashObj& x) const { //find the position in the table corresponding to x
		int currentPos = myhash(x); //original position
		while (array[currentPos].info != EMPTY && array[currentPos].element != x) { 
		//terminate when the position is found or x already exists in the table
			currentPos += 1; //linear probing
			if (currentPos >= array.size()) //mod operation
				currentPos -= array.size();
		}
		return currentPos;
	}

	void rehash() { //double the size of the array
		vector<HashEntry> oldArray = array; //to store the old array
		array.resize(nextPrime(2 * oldArray.size())); //set the array size to be the next prime number after twice old size
		for (int j = 0; j < array.size(); j++) //set the information of all elements of the new array to be EMPTY
			array[j].info = EMPTY;
		currentSize = 0;
		for (int i = 0; i < oldArray.size(); i++) //insert the elements in the old array into the new array
			if (oldArray[i].info == ACTIVE)
				insert(oldArray[i].element);
	}

	int hash(const string& x) const { //hash function with argument of string type
		int xVal = 0; //to store the value of the string
		for (int i = 0; i < 3; i++) //last 4 bits since the array size is 101
			xVal = xVal + pow(10, i) * (x[x.size() - 1 - i] - '0');
		int currentPos = xVal % array.size(); //mod operation
		return currentPos;
	}

	int myhash(const HashObj& x) const { //hash function with argument of HashObj type
		string xStr = x.getID(); //get the key string of the object
		return hash(xStr);
	}
};

bool isPrime(int n) { //if n is a prime number
	for (int i = 2; i <= n / 2; i++)
		if (n % i == 0) //if n has any factor no less than 2
			return false;
	return true;
}

int nextPrime(int n) { //to find the next prime number after n
	while (!isPrime(n)) //end loop when n is prime
		n++;
	return n;
}