#include <string>
#include <map>
#include <set>

std::set<std::string> BuildMapValuesSet(const std::map<int, std::string>& m) {
	std::set<std::string> setOfMapValues {};

	for (const auto& item : m) {
		setOfMapValues.insert(item.second);
	}//rof

	return setOfMapValues;
}
