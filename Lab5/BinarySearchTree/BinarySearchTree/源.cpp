#include "binarySearchTree.h"
#include <iostream>
#include <ctime>
using namespace std;
const int N = 20; //number of datas
const int MAX = 20; //max value of the data

template <typename T>
void visit(T d) {
	cout << d << " ";
}

int main() {
	srand((unsigned int)time(0));
	BinTree<int> tree;
	for (int i = 0; i < N; i++) {   //generate N random numbers and insert them into the tree one by one
		tree.insert(rand() % MAX);
	}
	cout << "Level traverse:" << endl;
	tree.print();
	cout << "Inordered traverse:" << endl;
	tree.traversal(visit);
	cout << endl;
	int d = rand() % MAX; //generate a random number and search it in the tree
	cout << "Search an element: " << d << " " << (tree.search(d) == 1 ? "true" : "flase") << endl;
	system ("pause");
	return 0;
}