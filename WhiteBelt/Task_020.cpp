#include <iostream>
#include <string>
#include <vector>
#include <map>

std::map<char, int> BuildCharCounters(const std::string& word) {
	std::map<char, int> counter {};

	for (const auto& w : word)
		++counter[w];

	return counter;
}

bool IsAnagram(const std::string& first, const std::string& second) {
	return BuildCharCounters(first) == BuildCharCounters(second);
}

int main() {
	int n = 0;
	std::cin >> n;

	for (int i = 0; i < n; ++i) {
		std::string first, second;
		std::cin >> first >> second;
		std::cout << (IsAnagram(first, second) ? "YES" : "NO") << std::endl;
	}

	return 0;
}
