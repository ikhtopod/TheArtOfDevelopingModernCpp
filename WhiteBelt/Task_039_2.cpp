#include <iostream>
#include <fstream>
#include <string>

int main() {
	std::string inFilename { "input.txt" };
	std::string outFilename { "output.txt" };

	std::ifstream infile { inFilename };
	std::ofstream outfile { outFilename };

	if (infile.is_open() && outfile.is_open()) {
		std::string line {};

		while (std::getline(infile, line)) {
			outfile << line << std::endl;
		}
	}

	return 0;
}
