#include <iostream>
#include <vector>

int Average(const std::vector<int>& numbers) {
	if (numbers.empty()) return 0;

	int sum = 0;
	for (const int& n : numbers) {
		sum += n;
	}//rof

	return sum / numbers.size();
}

void MoreThanAverage(
	const std::vector<int>& source,
	std::vector<int>& destination) {

	int average = Average(source);

	for (int i = 0; i < source.size(); ++i) {
		if (source[i] > average) {
			destination.push_back(i);
		}//fi
	}//rof
}

void PrintResult(const std::vector<int>& result) {
	std::cout << result.size() << std::endl;

	for (const int& i : result) {
		std::cout << i << " ";
	}//rof
}

int main() {
	int n = 0;
	std::cin >> n;

	std::vector<int> v(n);
	for (int& d : v) std::cin >> d;

	std::vector<int> moreThanAverage {};
	MoreThanAverage(v, moreThanAverage);

	PrintResult(moreThanAverage);

	return 0;
}
