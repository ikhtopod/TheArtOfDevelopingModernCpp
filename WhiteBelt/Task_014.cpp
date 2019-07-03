#include <iostream>
#include <string>
#include <vector>

#define DPRINT(ARG) std::cout << #ARG << ": " << ARG << std::endl


void MoveStrings(
	std::vector<std::string>& source,
	std::vector<std::string>& destination) {

	for (auto x : source) {
		destination.push_back(x);
	}

	source.clear();
}


int main() {
	std::vector<std::string> source { "a", "b", "c" };
	std::vector<std::string> destination { "z" };
	MoveStrings(source, destination);

	DPRINT(source.size());
	DPRINT(destination.size());

	return 0;
}