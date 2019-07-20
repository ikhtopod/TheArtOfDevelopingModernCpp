#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

template <typename T>
std::vector<T> FindGreaterElements(const std::set<T>& elements, const T& border) {
	auto greater_it = std::find_if(
		std::begin(elements),
		std::end(elements),
		[&border](const T& x) {
			return x > border;
		}
	);

	return { greater_it, std::end(elements) };
}

int main() {
	using namespace std;

	for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) {
		cout << x << " ";
	}
	cout << endl;

	string to_find = "Python";
	cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
	return 0;
}
