#include <iostream>
#include <utility>
#include <vector>
#include <map>

template <typename T>
T Sqr(T);

template <typename T>
std::vector<T> Sqr(const std::vector<T>&);

template <typename First, typename Second>
std::pair<First, Second> Sqr(const std::pair<First, Second>&);

template <typename Key, typename Value>
std::map<Key, Value> Sqr(const std::map<Key, Value>&);


template <typename T>
T Sqr(T x) {
	return x * x;
}

template <typename T>
std::vector<T> Sqr(const std::vector<T>& x) {
	std::vector<T> result {};

	for (const auto& i : x) {
		result.push_back(Sqr(i));
	}

	return result;
}

template <typename First, typename Second>
std::pair<First, Second> Sqr(const std::pair<First, Second>& x) {
	return std::make_pair(Sqr(x.first), Sqr(x.second));
}

template <typename Key, typename Value>
std::map<Key, Value> Sqr(const std::map<Key, Value>& x) {
	std::map<Key, Value> result {};

	for (const auto& [key, value] : x) {
		result[key] = Sqr(value);
	}

	return result;
}

/**
	Код должен вывести:
	\code
		vector: 1 4 9
		map of pairs:
		4 4 4
		7 16 9
	\endcode

	\return 0
*/
int main() {
	using namespace std;

	cout << "simple int number(2): " << Sqr(2) << endl;
	cout << "simple first float number(5.0f): " << Sqr(5.0f) << endl;
	cout << "simple second float number(7.7f): " << Sqr(7.7f) << endl;
	cout << "simple first double number(6.0): " << Sqr(6.0) << endl;
	cout << "simple second double number(12.11): " << Sqr(12.11) << endl;

	vector<int> v = { 1, 2, 3 };
	cout << "vector:";
	for (int x : Sqr(v)) {
		cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = {
	  {4, {2, 2}},
	  {7, {4, 3}}
	};
	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
		cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}

	return 0;
}

