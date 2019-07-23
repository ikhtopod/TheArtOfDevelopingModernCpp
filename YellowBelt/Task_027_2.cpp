#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <utility>
#include <iterator>
#include <sstream>

inline bool HasBracket(char first, char second) {
	return (first == '+' || first == '-') && (second == '*' || second == '/');
}

int main() {
	std::vector<std::pair<char, int>> operations(1);

	size_t n = 0;
	std::cin >> operations.front().second >> n;
	operations.front().first = '+';

	operations.resize(n + 1);
	for (auto it = std::next(std::begin(operations)); it != std::end(operations); std::advance(it, 1)) {
		std::cin >> it->first >> it->second;
	}

	std::deque<std::string> result {};
	result.push_back(std::to_string(operations.front().second));


	auto start = std::next(std::cbegin(operations));
	const auto finish = std::cend(operations);

	bool hasBracket = false;
	while (start != finish) {
		auto next = std::next(start);

		if (next == finish) {
			hasBracket = false;
		} else {
			hasBracket = HasBracket(start->first, next->first);
		}

		if (hasBracket) result.push_front("(");
		std::stringstream sstr {};
		sstr << ' ' << start->first << ' ' << start->second;
		result.push_back(sstr.str());
		if (hasBracket) result.push_back(")");

		std::advance(start, 1);
	}

	for (const auto& r : result) {
		std::cout << r;
	}

	return EXIT_SUCCESS;
}
