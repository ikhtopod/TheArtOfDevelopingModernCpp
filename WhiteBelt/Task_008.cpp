#include <iostream>

int main() {
	int a = 0, b = 0;

	std::cin >> a >> b;

	while (b != 0) {
		int tmp = a;
		a = b;
		b = tmp % b;
	}

	std::cout << a;

	return 0;
}
