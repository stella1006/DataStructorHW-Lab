#include "huffman.h"
#include <ctime>

#define SIZE  200



//int main(int argc, char *argv[]) {
//	if (argc != 3) {
//		cout << "a" << endl;
//		cout << "Usage:\n\t huffmanCoding(huffmanDecoding) inputfile outputfile" << endl;
//		exit(1);
//	}
//
//	string inputfile = "D:\\", outputfile = "D:\\", codefile = "D:\\code.txt";
//	inputfile += argv[1];
//	inputfile += ".txt";
//	outputfile += argv[2];
//	outputfile += ".huf";
//
//	ofstream out;
//	out.open(inputfile);
//	srand(time(0));
//	char c;
//	for (int i = 0; i < SIZE; i++) {
//		c = ('a' + rand() % 25);
//		out << c;
//	}
//
//	out.close();
//
//
//
//	huffman h(inputfile, outputfile, "D:\\code.txt");
//	h.create_pq();
//	h.create_huffman_tree();
//	h.calculate_huffman_codes(h.root);
//	h.save_to_file();
//	cout << endl;
//	
//	return 0;
//}

int main() {
	while (cin.get()) {
	string inputfile = "E:\\in.txt", outputfile = "E:\\out.txt", codefile = "E:\\code.txt";

	ofstream out;
	out.open(inputfile);
	srand(time(0));
	char c;
	for (int i = 0; i < SIZE; i++) {
		c = ('a' + rand() % 25);
		out << c;
	}

	out.close();

	huffman h(inputfile, outputfile, "E:\\code.txt");
	h.create_pq();
	h.create_huffman_tree();
	h.calculate_huffman_codes(h.root);
	h.save_to_file();
	cout << "input End" << endl;

	/*huffman h2(outputfile, "E:\\decode.txt", codefile);
	h2.huffman_decoding();

	cout << "output End" << endl;*/
	}
	system ("pause");
	return 0;
}
