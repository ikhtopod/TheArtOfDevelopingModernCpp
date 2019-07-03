#include <iostream>
#include <vector>

void Swap(int& x, int& y) {
	int tmp = x;
	x = y;
	y = tmp;
}

void Reverse(std::vector<int>& v) {
	for (int i = 0, j = v.size() - 1; i < j; ++i, --j) {
		Swap(v[i], v[j]);
	}//rof
}

int main() {
	std::vector<int> numbers = { 1, 5, 3, 4, 2 };
	Reverse(numbers);

	for (auto n : numbers) {
		std::cout << n << " ";
	}

	return 0;
}