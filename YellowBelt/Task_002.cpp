#include <iostream>
#include <vector>

int main() {
	size_t n = 0;
	std::cin >> n;

	std::vector<int> temp(n);

	int64_t average = 0;
	for (auto& t : temp) {
		std::cin >> t;
		average += static_cast<int64_t>(t);
	}

	average /= static_cast<int64_t>(temp.size());

	std::vector<size_t> result {};
	for (size_t i = 0; i < temp.size(); ++i) {
		if (static_cast<int64_t>(temp[i]) > average) {
			result.push_back(i);
		}
	}

	std::cout << result.size() << std::endl;
	for (const auto& r : result) {
		std::cout << r << " ";
	}

	return 0;
}
