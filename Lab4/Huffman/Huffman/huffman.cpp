#include "huffman.h"
#include <ctime>

#define SIZE  100
//void Encoding(char* a, char* b) {
//	/*huffman h(a, b);
//	h.creat_pq();
//	h.create_huffman_tree();
//	h.calculate_huffman_codes();
//	h.save_to_file();
//	cout << endl;*/
//	cout << 1 << endl;
//}


int main(int argc, char *argv[]) {
	if (argc != 3) {
		cout << "a" << endl;
		cout << "Usage:\n\t huffmanCoding(huffmanDecoding) inputfile outputfile" << endl;
		exit(1);
	}

	/*Encoding(argv[1], argv[2]);*/
	ofstream out;
	out.open(argv[1]);
	srand(time(0));
	char c;
	for (int i = 0; i < SIZE; i++) {
		c = ('a' + rand() % 25);
		out << c;
	}

	out.close();



	huffman h(argv[1], argv[2], "E:\\code.txt");
	h.create_pq();
	h.create_huffman_tree();
	h.calculate_huffman_codes(h.root);
	h.save_to_file();
	cout << endl;
	
	//Decoding(argv[1], argv[2]);
	
	//system("pause");
	return 0;
}