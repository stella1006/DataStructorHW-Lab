#include "huffman.h"

int main(int argc, char *argv[]) {
	if (argc != 3) { //if argc is not 3, output the right usage of this program and exit
		cout << "a" << endl;
		cout << "usage:\n\t huffmandecoding(huffmandecoding) inputfile outputfile" << endl;
		exit(1);
	}

	//only need to input the file name without prefix and postfix
	string inputfile = "d:\\", outputfile = "d:\\", codefile = "d:\\code.txt";
	inputfile += argv[1];
	inputfile += ".huf";
	outputfile += argv[2];
	outputfile += ".txt";


	huffman h(inputfile, outputfile, codefile);
	h.huffman_decoding();
	cout << endl;
	
	return 0;
}