#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

void PrintNumbers(const std::vector<int>& numbers) {
	for (const auto& n : numbers) {
		std::cout << n << " ";
	}

	std::cout << std::endl;
}

void PrintReversePermutations(std::vector<int>& numbers) {
	do {
		PrintNumbers(numbers);
	} while (std::prev_permutation(std::begin(numbers), std::end(numbers)));
}

int main() {
	int n = 1;
	std::cin >> n;

	std::vector<int> numbers(n);
	std::iota(std::rbegin(numbers), std::rend(numbers), 1);

	PrintReversePermutations(numbers);

	return 0;
}
