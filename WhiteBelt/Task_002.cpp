#include <iostream>

int main() {
	std::string strOne {};
	std::string strTwo {};
	std::string strThree {};

	std::cin >> strOne >> strTwo >> strThree;

	if (strOne < strTwo) {
		std::cout << (strOne < strThree ? strOne : strThree);
	} else {
		std::cout << (strTwo < strThree ? strTwo : strThree);
	}

	return 0;
}
