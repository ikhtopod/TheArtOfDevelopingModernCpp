#include <iostream>
#include <utility>
#include <vector>
#include <map>

template<typename First, typename Second>
std::pair<First, Second> operator*(const std::pair<First, Second>&, const std::pair<First, Second>&);

template<typename Key, typename Value>
std::map<Key, Value> operator*(const std::map<Key, Value>&, const std::map<Key, Value>&);

template<typename T>
std::vector<T> operator*(const std::vector<T>&, const std::vector<T>&);

template <typename T> T Sqr(T);



template<typename First, typename Second>
std::pair<First, Second> operator*(const std::pair<First, Second>& lhs, const std::pair<First, Second>& rhs) {
	return std::make_pair(lhs.first * rhs.first, lhs.second * rhs.second);
}

template<typename Key, typename Value>
std::map<Key, Value> operator*(const std::map<Key, Value>& lhs, const std::map<Key, Value>& rhs) {
	std::map<Key, Value> result {};

	for (const auto& [key, value] : lhs) {
		result[key] = value * rhs.at(key);
	}

	return result;
}

template<typename T>
std::vector<T> operator*(const std::vector<T>& lhs, const std::vector<T>& rhs) {
	std::vector<T> result {};

	for (size_t i = 0; i < lhs.size(); ++i) {
		result.push_back(lhs[i] * rhs[i]);
	}

	return result;
}

template <typename T>
T Sqr(T x) {
	return x * x;
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

