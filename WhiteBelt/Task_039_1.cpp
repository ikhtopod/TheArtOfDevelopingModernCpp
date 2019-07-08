#include <iostream>
#include <fstream>
#include <string>

int ma1in() {
	std::string filename { "input.txt" };

	std::ifstream infile { filename };

	if (infile.is_open()) {
		std::cout << infile.rdbuf();
	}

	return 0;
}
