#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <iterator>
#include <algorithm>

template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix) {
	return std::equal_range(range_begin, range_end, std::string { prefix },
							[](const auto& x, const auto& y) { return x[0] < y[0]; });
}

int main() {
	using namespace std;

	const vector<string> sorted_strings = { "moscow", "murmansk", "vologda" };

	const auto m_result =
		FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
	for (auto it = m_result.first; it != m_result.second; ++it) {
		cout << *it << " ";
	}
	cout << endl;

	const auto p_result =
		FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
	cout << (p_result.first - begin(sorted_strings)) << " " <<
		(p_result.second - begin(sorted_strings)) << endl;

	const auto z_result =
		FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
	cout << (z_result.first - begin(sorted_strings)) << " " <<
		(z_result.second - begin(sorted_strings)) << endl;

	return 0;
}

