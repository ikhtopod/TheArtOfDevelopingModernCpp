#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	int count_elements = std::distance(range_begin, range_end);
	if (std::distance(range_begin, range_end) < 2) return;

	int third_of_count_of_elements = count_elements / 3;
	auto left_middle_it = range_begin + third_of_count_of_elements;
	auto right_middle_it = left_middle_it + third_of_count_of_elements;

	std::vector<typename RandomIt::value_type> left_part_of_elements { range_begin, left_middle_it };
	std::vector<typename RandomIt::value_type> middle_part_of_elements { left_middle_it, right_middle_it };
	std::vector<typename RandomIt::value_type> right_part_of_elements { right_middle_it, range_end };

	MergeSort(std::begin(left_part_of_elements), std::end(left_part_of_elements));
	MergeSort(std::begin(middle_part_of_elements), std::end(middle_part_of_elements));
	MergeSort(std::begin(right_part_of_elements), std::end(right_part_of_elements));

	std::vector<typename RandomIt::value_type> merged_left_and_middle_parts {};
	std::merge(std::begin(left_part_of_elements), std::end(left_part_of_elements),
			   std::begin(middle_part_of_elements), std::end(middle_part_of_elements),
			   std::back_inserter(merged_left_and_middle_parts));

	std::merge(std::begin(merged_left_and_middle_parts), std::end(merged_left_and_middle_parts),
			   std::begin(right_part_of_elements), std::end(right_part_of_elements),
			   range_begin);
}

int main() {
	using namespace std;

	vector<int> v = { 6, 4, 7, 6, 4, 4, 0, 1, 5 };
	MergeSort(begin(v), end(v));
	for (int x : v) {
		cout << x << " ";
	}
	cout << endl;

	return 0;
}

// 0 1 4 4 4 5 6 6 7
