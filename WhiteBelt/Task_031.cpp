#include <algorithm>
#include <string>
#include <vector>
#include <map>

class Person {
private:
	std::map<int, std::string> m_firstname {};
	std::map<int, std::string> m_lastname {};

	static std::string GetChangeByYear(int year, const std::map<int, std::string>& m);

public:
	void ChangeFirstName(int year, const std::string& first_name);
	void ChangeLastName(int year, const std::string& last_name);
	std::string GetFullName(int year);
};


std::string Person::GetChangeByYear(int year, const std::map<int, std::string>& m) {
	std::string result {};

	for (const auto& i : m) {
		if (i.first > year) break;
		result = i.second;
	}

	return result;
}

// �������� ���� ��������� ����� �� first_name � ��� year
void Person::ChangeFirstName(int year, const std::string& first_name) {
	m_firstname[year] = first_name;
}

// �������� ���� ��������� ������� �� last_name � ��� year
void Person::ChangeLastName(int year, const std::string& last_name) {
	m_lastname[year] = last_name;
}

// �������� ��� � ������� �� ��������� �� ����� ���� year
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
