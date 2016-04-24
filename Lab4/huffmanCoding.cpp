#include "huffman.h"
#include <ctime>

#define SIZE  100 //size of in_file



int main(int argc, char *argv[]) {
	if (argc != 3) { //if argc is not 3, output the right usage of this program and exit
		cout << "a" << endl;
		cout << "Usage:\n\t huffmanCoding(huffmanDecoding) inputfile outputfile" << endl;
		exit(1);
	}
	
	//only need to input the file name without prefix and postfix
	string inputfile = "D:\\", outputfile = "D:\\", codefile = "D:\\code.txt";
	inputfile += argv[1];
	inputfile += ".txt";
	outputfile += argv[2];
	outputfile += ".huf";

	ofstream out;
	out.open(inputfile);
	srand(time(0));
	char c;
	for (int i = 0; i < SIZE; i++) { //generate 100 alphabets randomly into a file
		c = ('a' + rand() % 26);
		out << c;
	}

	out.close();



	huffman h(inputfile, outputfile, "D:\\code.txt");
	h.create_pq();
	h.create_huffman_tree();
	h.calculate_huffman_codes(h.root);
	h.save_to_file();
	cout << endl;
	
	return 0;
}