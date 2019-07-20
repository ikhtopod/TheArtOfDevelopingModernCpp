#include <iostream>
#include <algorithm>
#include <vector>

void PrintVectorPart(const std::vector<int>& numbers) {
	auto it = std::find_if(
		std::begin(numbers),
		std::end(numbers),
		[](int x) {
			return x < 0;
		}
	);

	while (it != std::begin(numbers)) {
		std::cout << *(--it) << ' ';
	}//rof
}


int main() {
	using namespace std;

	PrintVectorPart({ 6, 1, 8, -5, 4 });
	cout << endl;
	PrintVectorPart({ -6, 1, 8, -5, 4 });  // ничего не выведется
	cout << endl;
	PrintVectorPart({ 6, 1, 8, 5, 4 });
	cout << endl;

	return 0;
}
