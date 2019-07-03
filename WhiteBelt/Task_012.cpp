#include <iostream>
#include <string>
#include <vector>

bool IsPalindrom(std::string str) {
	if (str.empty()) return true;

	for (size_t i = 0, j = str.size() - 1; i < j; ++i, --j) {
		if (str[i] != str[j]) {
			return false;
		}//fi
	}//rof

	return true;
}

std::vector<std::string> PalindromFilter(std::vector<std::string> words, int minLength) {
	std::vector<std::string> newWords {};

	for (std::string word : words) {
		if (word.length() < minLength) continue;
		if (IsPalindrom(word)) newWords.push_back(word);
	}//rof

	return newWords;
}

int main() {
	for (auto word : PalindromFilter({ "abacaba", "aba" }, 5)) {
		std::cout << word << std::endl;
	}//rof
	std::cout << std::endl;

	for (auto word : PalindromFilter({ "abacaba", "aba" }, 2)) {
		std::cout << word << std::endl;
	}//rof
	std::cout << std::endl;

	for (auto word : PalindromFilter({ "weew", "bro", "code" }, 4)) {
		std::cout << word << std::endl;
	}//rof
	std::cout << std::endl;


	return 0;
}