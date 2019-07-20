#include <iostream>
#include <algorithm>
#include <vector>

void FillReverseRangeFromNTo1(std::vector<int>& numbers, int n) {
	numbers.clear();
	numbers.resize(n);

	int counter = n;
	for (auto& n : numbers) {
		n = counter--;
	}
}

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

	std::vector<int> numbers {};
	FillReverseRangeFromNTo1(numbers, n);
	PrintReversePermutations(numbers);

	return 0;
}