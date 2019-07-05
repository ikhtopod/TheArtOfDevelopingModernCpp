#include <algorithm>
#include <string>
#include <vector>
#include <map>

class Person {
private:
	std::map<int, std::string> m_firstname {};
	std::map<int, std::string> m_lastname {};

	static std::string GetChangeByYear(int year, const std::map<int, std::string>& m);
	static std::vector<std::string> GetPrevChangeByYear(int year, const std::map<int, std::string>& m);
	static std::string NamesToString(const std::vector<std::string>& v);

public:
	void ChangeFirstName(int year, const std::string& first_name);
	void ChangeLastName(int year, const std::string& last_name);
	std::string GetFullName(int year);
	std::string GetFullNameWithHistory(int year);
};


std::string Person::GetChangeByYear(int year, const std::map<int, std::string>& m) {
	std::string result {};

	for (const auto& i : m) {
		if (i.first > year) break;
		result = i.second;
	}//rof

	return result;
}

std::vector<std::string> Person::GetPrevChangeByYear(int year, const std::map<int, std::string>& m) {
	std::vector<std::string> result {};

	std::string prevName {};
	std::string name {};

	for (const auto& i : m) {
		if (i.first > year) break;
		prevName = name;
		name = i.second;

		if ((!result.empty() && prevName == result.back()) || prevName.empty()) continue;

		if (std::find(std::cbegin(result), std::cend(result), prevName) == std::cend(result)) {
			result.push_back(prevName);
		}//fi
	}//rof

	std::reverse(std::begin(result), std::end(result));

	while (!result.empty() && result[0] == name)
		result.erase(std::begin(result));

	return result;
}

std::string Person::NamesToString(const std::vector<std::string>& v) {
	std::string result {};

	if (v.size() >= 1) {
		result = v[0];

		for (size_t i = 1; i < v.size(); ++i) {
			result += ", " + v[i];
		}//rof
	}//fi

	return result;
}


// добавить факт изменения имени на first_name в год year
void Person::ChangeFirstName(int year, const std::string& first_name) {
	m_firstname[year] = first_name;
}

// добавить факт изменения фамилии на last_name в год year
void Person::ChangeLastName(int year, const std::string& last_name) {
	m_lastname[year] = last_name;
}

// получить имя и фамилию по состоянию на конец года year
std::string Person::GetFullName(int year) {
	std::string result { "Incognito" };

	std::string name = GetChangeByYear(year, m_firstname);
	std::string surname = GetChangeByYear(year, m_lastname);

	if (!name.empty() && !surname.empty()) {
		result = name + " " + surname;
	} else if (!name.empty()) {
		result = name + " with unknown last name";
	} else if (!surname.empty()) {
		result = surname + " with unknown first name";
	}

	return result;
}

// получить все имена и фамилии по состоянию на конец года year
std::string Person::GetFullNameWithHistory(int year) {
	std::string result { "Incognito" };

	std::string name = GetChangeByYear(year, m_firstname);
	std::string surname = GetChangeByYear(year, m_lastname);

	std::string prevNames = NamesToString(GetPrevChangeByYear(year, m_firstname));
	std::string prevSurnames = NamesToString(GetPrevChangeByYear(year, m_lastname));

	if (!name.empty() && !surname.empty()) {

		result = name + (prevNames.empty() ? " " : " (" + prevNames + ") ") +
			surname + (prevSurnames.empty() ? "" : " (" + prevSurnames + ")");
	} else if (!name.empty()) {
		result = name + (prevNames.empty() ? " " : " (" + prevNames + ") ") + "with unknown last name";
	} else if (!surname.empty()) {
		result = surname + (prevSurnames.empty() ? " " : " (" + prevSurnames + ") ") + "with unknown first name";
	}

	return result;
}
