#include <iostream>

bool IsPalindrom(std::string str) {
	if (str.empty()) return true;

	for (size_t i = 0, j = str.size() - 1; i < j; ++i, --j) {
		if (str[i] != str[j]) {
			return false;
		}//fi
	}//rof

	return true;
}

#define DPRINT(ARG) std::cout << #ARG << ": " << ARG << std::endl

int main() {
	DPRINT(IsPalindrom("madam"));
	DPRINT(IsPalindrom("gentleman"));
	DPRINT(IsPalindrom("X"));
	DPRINT(IsPalindrom(""));

	return 0;
}
