#include <iostream>
#include <cassert>

int Sum(int x, int y) { return x + y; }

#define RUN_TEST(ARG) ARG; std::cout << #ARG << " is OK" << std::endl

void Sum_Test() {
	assert(Sum(2, 3) == 5);
	assert(Sum(-2, -3) == -5);
	assert(Sum(-2, 0) == -2);
	assert(Sum(-2, 0) == 2); // wrong
	assert(Sum(-2, 2) == 0);
}

void RunAllTests() {
	RUN_TEST(Sum_Test());
}

int main() {
	RunAllTests();

	return 0;
}
