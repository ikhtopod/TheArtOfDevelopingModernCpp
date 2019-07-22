#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <iterator>

bool HasBraket(char start, char next) {
	return (start == '*' || start == '/') && (next == '+' || next == '-');
}

template <typename RIter>
void PrintExpression(RIter start, RIter finish, bool hasBraket = false) {
	if (hasBraket) std::cout << '(';

	if (start != finish) {
		auto next = std::next(start);

		if (next == finish) {
			std::cout << start->second;
		} else {
			if (std::next(next) == finish) {
				PrintExpression(next, finish);
			} else {
				PrintExpression(next, finish, HasBraket(start->first, next->first));
			}

			std::cout << ' ' << start->first << ' ' << start->second;
		}
	}

	if (hasBraket) std::cout << ')';
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

	PrintExpression(std::rbegin(operations), std::rend(operations));

	return EXIT_SUCCESS;
}
