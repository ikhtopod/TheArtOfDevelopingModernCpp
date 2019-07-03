#include <iostream>

int Factorial(int n) {
	if (n < 1) return 1;

	int x = 1;

	for (int i = 1; i <= n; ++i) {
		x *= i;
	}

	return x;
}

int main() {
	std::cout << Factorial(5);

	return 0;
}