#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

int main() {
	std::string filename { "input.txt" };

	std::ifstream infile { filename };

	if (infile.is_open()) {
		std::cout << std::fixed << std::setprecision(3);

		double num = 0.0;
		while (infile >> num) {
			std::cout << num << std::endl;
		}
	}

	return 0;
}
