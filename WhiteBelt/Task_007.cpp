#include <iostream>
#include <string>

int main() {
	std::string str {};

	std::cin >> str;

	int fCounter = 0;
	int result = -2;

	for (int i = 0; i < str.size(); ++i) {
		if (str.at(i) == 'f') {
			fCounter++;

			if (fCounter == 1) {
				result = -1;
			} else if (fCounter == 2) {
				result = i;
				break;
			}//fi
		}//fi
	}//rof

	std::cout << result;

	return 0;
}
