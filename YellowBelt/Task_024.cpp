#include <iostream>
#include <algorithm>
#include <set>

using SetCIter = std::set<int>::const_iterator;

SetCIter FindNearestElement(const std::set<int>& numbers, int border) {
	if (numbers.empty()) return std::cend(numbers);

	auto lower = numbers.lower_bound(border);

	if (lower == std::cend(numbers)) {
		return std::prev(std::cend(numbers));
	} else if (lower == std::cbegin(numbers) || *lower == border) {
		return lower;
	}

	auto prev_lower = std::prev(lower);

	int left_dist = border - *prev_lower;
	int right_dist = *lower - border;

	return left_dist <= right_dist ? prev_lower : lower;
}

int main() {
	using namespace std;

	set<int> numbers = { 1, 4, 6 };
	cout <<
		*FindNearestElement(numbers, 0) << " " <<
		*FindNearestElement(numbers, 3) << " " <<
		*FindNearestElement(numbers, 5) << " " <<
		*FindNearestElement(numbers, 6) << " " <<
		*FindNearestElement(numbers, 100) << endl;

	set<int> empty_set;

	cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;

	return 0;
}
