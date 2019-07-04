#include <iostream>
#include <string>
#include <set>

int main() {
	int n = 0;
	std::cin >> n;

	std::set<std::string> strings {};

	for (int i = 0; i < n; ++i) {
		std::string str {};
		std::cin >> str;
		strings.insert(str);
	}//rof

	std::cout << strings.size();

	return 0;
}
