#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

const std::string filename { "input.txt" };

int main() {
	std::ifstream infile { filename };

	if (infile.is_open()) {
		int n = 0, m = 0;

		infile >> n >> m;

		int num = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				infile >> num;
				infile.ignore(1);
				std::cout << std::setw(10) << num;

				if (j < m - 1) {
					std::cout << " ";
				}//fi
			}//rof

			if (i < n - 1) {
				std::cout << std::endl;
			}//fi
		}//rof
	}//fi

	return 0;
}
