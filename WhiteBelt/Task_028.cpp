#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

int main() {
	int n = 0;
	std::cin >> n;

	std::vector<int> v(n);
	for (auto& i : v)
		std::cin >> i;

	std::sort(std::begin(v), std::end(v),
			  [](int x, int y) {
				  return std::abs(x) < std::abs(y);
			  });

	for (const auto& i : v)
		std::cout << i << " ";

	return 0;
}
