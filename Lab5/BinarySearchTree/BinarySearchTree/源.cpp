#include "binarySearchTree.h"
#include <iostream>
#include <ctime>
using namespace std;

template <typename T>
void visit(T d) {
	cout << d << " ";
}

int main() {
	srand((unsigned int)time(0));
	BinTree<int> tree;
	//BinTree<int> tree2(tree1);
	for (int i = 0; i < 20; i++) {
		tree.insert(rand() % 15);
	}
	cout << "Level traverse:" << endl;
	tree.print();
	cout << "Inordered traverse:" << endl;
	tree.traversal(visit);

	system ("pause");
	return 0;
}
