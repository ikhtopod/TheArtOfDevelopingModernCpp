#include <iostream>

int main() {
	int a = 0, b = 0;

	std::cin >> a >> b;

	for (int i = a; i <= b; ++i) {
		if ((i & 0x1) == 0) {
			std::cout << i << " ";
		}
	}

	return 0;
}
