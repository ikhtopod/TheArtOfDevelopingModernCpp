#include <iostream>

void UpdateIfGreater(const int& first, int& second) {
	if (first > second) second = first;
}

#define DPRINT(ARG) std::cout << #ARG << ": " << ARG << std::endl

int main() {
	int a = 4;
	int b = 2;

	UpdateIfGreater(a, b);

	DPRINT(a);
	DPRINT(b);

	return 0;
}
