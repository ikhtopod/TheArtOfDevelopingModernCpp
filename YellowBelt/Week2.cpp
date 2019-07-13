#include <iostream>

#define DPRINT(ARG) std::cout << #ARG << ": " << ARG << std::endl

int main() {
	DPRINT("Howdy, World!");

	return 0;
}
