#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <utility>
#include <sstream>

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
	if (operations.size() > 1) {
		result.push_front("(");
		result.push_back(")");
	}

	bool hasBracket = true;
	const auto finish = std::cend(operations);
	for (auto start = std::next(std::cbegin(operations)); start != finish; std::advance(start, 1)) {
		if (std::next(start) == finish) {
			if (hasBracket) hasBracket = false;
		} else {
			if (!hasBracket) hasBracket = true;
		}

		if (hasBracket) result.push_front("(");
		std::stringstream sstr {};
		sstr << ' ' << start->first << ' ' << start->second;
		result.push_back(sstr.str());
		if (hasBracket) result.push_back(")");
	}

	for (const auto& r : result) {
		std::cout << r;
	}

	return EXIT_SUCCESS;
}
