#include <iostream>

int main() {
	double n, a, b, x, y;

	std::cin >> n >> a >> b >> x >> y;

	if (a < b) {
		if (n <= a) {
			std::cout << n;
		} else if (n > a && n <= b) {
			std::cout << n * ((100.0 - x) / 100.0);
		} else {
			std::cout << n * ((100.0 - y) / 100.0);
		}
	}

	return 0;
}
