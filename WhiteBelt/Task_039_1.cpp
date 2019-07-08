#include <iostream>
#include <fstream>
#include <string>

int main() {
	std::string filename { "input.txt" };

	std::ifstream infile { filename };

	if (infile.is_open()) {
		std::cout << infile.rdbuf();
	}

	return 0;
}
