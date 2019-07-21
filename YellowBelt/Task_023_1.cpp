#include <iostream>
#include <algorithm>
#include <vector>

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	int count_elements = std::distance(range_begin, range_end);
	if (count_elements < 2) return;

	auto middle_it = range_begin + (count_elements / 2);
	std::vector<typename RandomIt::value_type> left_half_of_elements { range_begin, middle_it };
	std::vector<typename RandomIt::value_type> right_half_of_elements { middle_it, range_end };

	MergeSort(std::begin(left_half_of_elements), std::end(left_half_of_elements));
	MergeSort(std::begin(right_half_of_elements), std::end(right_half_of_elements));

	std::merge(std::begin(left_half_of_elements), std::end(left_half_of_elements),
			   std::begin(right_half_of_elements), std::end(right_half_of_elements),
			   range_begin);
}

int main() {
	using namespace std;

	//vector<int> v = { 6, 4, 7, 6, 4, 4, 0, 1 };
	vector<int> v = { 8, 6, 4, 7, 6, 4, 4, 0, 1 };
	MergeSort(begin(v), end(v));
	for (int x : v) {
		cout << x << " ";
	}
	cout << endl;

	return 0;
}

// 0 1 4 4 4 6 6 7