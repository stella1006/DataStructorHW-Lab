#include "huffman.h"

int main(int argc, char *argv[]) {
	if (argc != 3) {
		cout << "a" << endl;
		cout << "Usage:\n\t huffmanDecoding(huffmanDecoding) inputfile outputfile" << endl;
		exit(1);
	}

	huffman h(argv[1], argv[2], argv[3]);
	h.huffman_decoding();
	cout << endl;
	
	return 0;
}