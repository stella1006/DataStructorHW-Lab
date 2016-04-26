#include "huffman.h"

int main() {
	while (cin.get()) {
	string inputfile = "E:\\int.txt", outputfile = "E:\\out.txt", codefile = "E:\\code.txt";

	

	huffman h2(outputfile, "E:\\decode.txt", codefile);
	h2.huffman_decoding();

	cout << "output End" << endl;
	}
	system ("pause");
	return 0;
}