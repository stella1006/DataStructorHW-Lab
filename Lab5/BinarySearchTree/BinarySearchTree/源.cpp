#include "binarySearchTree.h"
#include <iostream>
#include <ctime>
using namespace std;

int main() {
	srand(time(0));
	BinTree<int> tree;
	for (int i = 0; i < 20; i++) {
		tree.insert(rand() % 15);
	}
	tree.print();
	tree.traversal();

	system ("pause");
	return 0;
}
