#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

int main() {
	int n = 0;
	std::cin >> n;

	std::vector<std::string> v(n);
	for (auto& i : v)
		std::cin >> i;

	std::sort(std::begin(v), std::end(v),
			  [](std::string x, std::string y) {
				  std::transform(std::begin(x), std::end(x), std::begin(x), toupper);
				  std::transform(std::begin(y), std::end(y), std::begin(y), toupper);
				  return x < y;
			  });

	for (const auto& i : v)
		std::cout << i << " ";
	
	return 0;
}
