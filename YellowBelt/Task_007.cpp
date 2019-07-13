#include <stdexcept>
#include <iostream>
#include <string>
#include <map>

template <typename Key, typename Value>
Value& GetRefStrict(std::map<Key, Value>&, Key);

template <typename Key, typename Value>
Value& GetRefStrict(std::map<Key, Value>& m, Key k) {
	try {
		return m.at(k);
	} catch (const std::out_of_range&) {
		throw std::runtime_error { "" };
	}
}


int main() {
	using namespace std;

	map<int, string> m = { {0, "value"} };
	string& item = GetRefStrict(m, 0);
	item = "newvalue";
	cout << m[0] << endl; // выведет newvalue

	return 0;
}
