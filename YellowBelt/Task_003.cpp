#include <iostream>
#include <vector>

int main() {
	uint32_t n;
	uint16_t r;
	std::cin >> n >> r;

	uint64_t result = 0;
	for (uint32_t i = 0; i < n; ++i) {
		uint32_t w, h, d;
		std::cin >> w >> h >> d;
		result += static_cast<uint64_t>(w) * h * d;
	}

	result *= r;

	std::cout << result;

	return 0;
}
