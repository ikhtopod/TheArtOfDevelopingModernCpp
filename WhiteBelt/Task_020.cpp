#include <iostream>
#include <string>
#include <vector>
#include <map>

std::map<char, int> BuildCharCounters(const std::string& word) {
	std::map<char, int> m {};

	for (const auto& w : word) m[w]++;

	return m;
}

bool IsAnagram(const std::string& first, const std::string& second) {
	return BuildCharCounters(first) == BuildCharCounters(second);
}

int main() {
	int n = 0;
	std::cin >> n;

	std::vector<std::string> result {};
	for (int i = 0; i < n; ++i) {
		std::string first, second;
		std::cin >> first >> second;
		result.push_back(IsAnagram(first, second) ? "YES" : "NO");
	}

	for (const auto& r : result) {
		std::cout << r << std::endl;
	}

	return 0;
}
