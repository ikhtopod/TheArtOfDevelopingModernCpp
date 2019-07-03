#include <iostream>
#include <string>

int main() {
	int n = 0;

	std::cin >> n;

	if (n <= 0) return 0;

	std::string result {};

	for (int i = n; i != 0; i >>= 1) {
		if ((i & 0x1) == 0) {
			result.push_back('0');
		} else {
			result.push_back('1');
		}
	}

	for (size_t i = 0, j = result.size() - 1; i < j; ++i, --j) {
		int tmp = result[i];
		result[i] = result[j];
		result[j] = tmp;
	}

	std::cout << result;

	return 0;
}