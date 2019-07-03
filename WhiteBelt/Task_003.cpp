#include <iostream>
#include <cmath>

int main() {
	double a = 0, b = 0, c = 0;

	std::cin >> a >> b >> c;

	if (a != 0 && b != 0 && c != 0) {
		double d = (b * b) - (4 * a * c);

		if (d > 0) {
			std::cout <<
				((-b + std::sqrt(d)) / (2 * a)) << " " <<
				((-b - std::sqrt(d)) / (2 * a));
		} else if (d == 0) {
			std::cout << (-b / (2 * a));
		}//fi
	} else if (a == 0 && b != 0 && c != 0) {
		std::cout << -(c / b);
	} else if (a != 0 && b != 0 && c == 0) {
		std::cout << 0 << " " << -(b / a);
	} else if (a != 0 && b == 0 && c == 0) {
		std::cout << 0 << " " << 0;
	} else if (a == 0 && b != 0 && c == 0) {
		std::cout << 0;
	}//fi

	return 0;
}
