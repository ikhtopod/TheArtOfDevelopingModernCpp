#include <iostream>
#include <cassert>

int Sum(int x, int y) { return x + y; }

#define RUN_TEST(ARG) ARG; std::cout << #ARG << " is OK" << std::endl

void Sum_Test() {
	assert(Sum(2, 3) == 5);
	assert(Sum(-2, -3) == -5);
	assert(Sum(-2, 0) == -2);
	//assert(Sum(-2, 0) == 2); // wrong
	assert(Sum(-2, 2) == 0);
}
void Sum_Test2() {
	assert(Sum(2, 3) == 5);
	assert(Sum(-2, -3) == -5);
	assert(Sum(-2, 0) == -2);
	assert(Sum(-2, 0) == 2); // wrong
	assert(Sum(-2, 2) == 0);
}

bool RunAllTests() {
	RUN_TEST(Sum_Test());
	RUN_TEST(Sum_Test2());

	return true;
}

int main() {
	if (RunAllTests()) return 0;

	return 0;
}