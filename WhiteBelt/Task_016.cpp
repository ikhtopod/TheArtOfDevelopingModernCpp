#include <iostream>
#include <vector>

void Swap(int& x, int& y) {
	int tmp = x;
	x = y;
	y = tmp;
}

std::vector<int> Reversed(const std::vector<int>& v) {
	std::vector<int> result = v;

	for (int i = 0, j = result.size() - 1; i < j; ++i, --j) {
		Swap(result[i], result[j]);
	}//rof

	return result;
}

int main() {
	std::vector<int> numbers = { 1, 5, 3, 4, 2 };
	numbers = Reversed(numbers);

	for (auto n : numbers) {
		std::cout << n << " ";
	}

	return 0;
}