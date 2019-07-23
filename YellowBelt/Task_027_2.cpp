#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <utility>
#include <iterator>
#include <sstream>

bool HasBracket(char prev, char start) {
	return (prev == '+' || prev == '-') && (start == '*' || start == '/');
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

	bool hasBracket = false;

	auto prev = std::cbegin(operations);
	auto start = std::next(prev);
	const auto finish = std::cend(operations);

	while (start != finish) {
		if (HasBracket(prev->first, start->first) || std::next(start) == finish) {
			if (hasBracket) hasBracket = false;
		} else {
			if (!hasBracket) hasBracket = true;
		}

		if (hasBracket) result.push_front("(");
		std::stringstream sstr {};
		sstr << ' ' << start->first << ' ' << start->second;
		result.push_back(sstr.str());
		if (hasBracket) result.push_back(")");

		std::advance(prev, 1);
		std::advance(start, 1);
	}

	for (const auto& r : result) {
		std::cout << r;
	}

	return EXIT_SUCCESS;
}
