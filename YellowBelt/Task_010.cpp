#include <cstdlib>
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <stdexcept>
#include <utility>
#include <vector>
#include <map>
#include <set>

#pragma region Unit Test System

namespace ru::lifanoff::utest {

// begin prototypes
template <class Value>
std::ostream& operator<<(std::ostream& lhs, const std::vector<Value>& rhs);

template <class Value>
std::ostream& operator<<(std::ostream& lhs, const std::set<Value>& rhs);

template <class First, class Second>
std::ostream& operator<<(std::ostream& lhs, const std::pair<First, Second>& rhs);

template <class Key, class Value>
std::ostream& operator<<(std::ostream& lhs, const std::map<Key, Value>& rhs);


// end prototypes

namespace additional {

template <class Collection>
std::ostream& PrintCollection(std::ostream& lhs, const Collection& rhs) {
	lhs << '{';

	bool first = true;
	for (const auto& value : rhs) {
		if (first) {
			first = false;
		} else {
			lhs << ", ";
		}//fi

		lhs << value;
	}//rof

	return lhs << '}';
}

} //! additional

template <class Value>
std::ostream& operator<<(std::ostream& lhs, const std::vector<Value>& rhs) {
	return additional::PrintCollection(lhs, rhs);
}

template <class Value>
std::ostream& operator<<(std::ostream& lhs, const std::set<Value>& rhs) {
	return additional::PrintCollection(lhs, rhs);
}

template <class First, class Second>
std::ostream& operator<<(std::ostream& lhs, const std::pair<First, Second>& rhs) {
	return lhs << '{' << rhs.first << ": " << rhs.second << '}';
}

template <class Key, class Value>
std::ostream& operator<<(std::ostream& lhs, const std::map<Key, Value>& rhs) {
	lhs << '{';

	bool first = true;
	for (const auto& item : rhs) {
		if (first) {
			first = false;
		} else {
			lhs << ", ";
		}//fi

		lhs << item.first << ": " << item.second;
	}//rof

	return lhs << '}';
}

template <class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint) {
	if (t != u) {
		std::ostringstream oss {};
		oss << "Assertion failed: " <<
			t << " != " << u <<
			" hint: " << hint;
		throw std::runtime_error { oss.str() };
	}//fi
}

template <class T, class U>
void AssertEqual(const T& t, const U& u) {
	AssertEqual(t, u, {});
}

void Assert(bool b, const std::string& hint) {
	AssertEqual(b, true, hint);
}

void Assert(bool b) {
	AssertEqual(b, true, {});
}


class TestRunner final {
private:
	size_t m_failCounter = 0;

public:
	TestRunner() = default;
	~TestRunner();

	template <class TestFunc>
	void RunTest(TestFunc func, const std::string& funcName);
};

TestRunner::~TestRunner() {
	if (this->m_failCounter > 0) {
		std::cout << this->m_failCounter << " unit tests failed. Terminate";
		exit(EXIT_FAILURE);
	}
}

template <class TestFunc>
void TestRunner::RunTest(TestFunc func, const std::string& funcName) {
	std::cout << funcName << ' ';

	try {
		func();
		std::cerr << "OK" << std::endl;
	} catch (const std::exception& e) {
		this->m_failCounter++;
		std::cerr << "failed: " << e.what() << std::endl;
	} catch (...) {
		this->m_failCounter++;
		std::cerr << "Unknown exception caught" << std::endl;
	}
}

}//! namespace ru::lifanoff::utest

#pragma endregion Unit Test System

#pragma region Person
class Person {
private:
	std::map<int, std::string> m_firstname {};
	std::map<int, std::string> m_lastname {};

	static std::string GetChangeByYear(int year, const std::map<int, std::string>& m) {
		std::string result {};

		for (const auto& i : m) {
			if (i.first > year) break;
			result = i.second;
		}

		return result;
	}

public:
	// добавить факт изменения имени на first_name в год year
	void ChangeFirstName(int year, const std::string& first_name) {
		m_firstname[year] = first_name;
	}

	// добавить факт изменения фамилии на last_name в год year
	void ChangeLastName(int year, const std::string& last_name) {
		m_lastname[year] = last_name;
	}

	// получить имя и фамилию по состоянию на конец года year
	std::string GetFullName(int year) {
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
};
#pragma endregion Person

namespace UTest = ru::lifanoff::utest;

/* Begin Tests */

void Person_WhenCalledGetFullName_ReturnsIncognito() {
	const std::string mustReturn = "Incognito";

	Person person {};

	{
		for (int year = 1900; year <= 2019; ++year) {
			UTest::AssertEqual(person.GetFullName(year), mustReturn, "GetFullName(" + std::to_string(year) + ")");
		}//rof
	}

	{
		person.ChangeFirstName(1953, "David");
		person.ChangeLastName(1955, "Thornton");

		int year = 1945;
		UTest::AssertEqual(person.GetFullName(year), mustReturn, "GetFullName(" + std::to_string(year) + ")");
	}
}

void Person_WhenCalledGetFullName_ReturnsFirstName() {
	const std::string append = " with unknown last name";

	Person person {};

	{
		person.ChangeFirstName(1953, "David");

		int year = 1953;
		UTest::AssertEqual(person.GetFullName(year), "David" + append, "GetFullName(" + std::to_string(year) + ")");
	}

	{
		person.ChangeFirstName(1963, "George");

		int year = 1954;
		UTest::AssertEqual(person.GetFullName(year), "David" + append, "GetFullName(" + std::to_string(year) + ")");
		year = 1964;
		UTest::AssertEqual(person.GetFullName(year), "George" + append, "GetFullName(" + std::to_string(year) + ")");
	}
}

void Person_WhenCalledGetFullName_ReturnsLastName() {
	const std::string append = " with unknown first name";

	Person person {};

	{
		person.ChangeLastName(1953, "Thornton");

		int year = 1953;
		UTest::AssertEqual(person.GetFullName(year), "Thornton" + append, "GetFullName(" + std::to_string(year) + ")");
	}

	{
		person.ChangeLastName(1963, "Mills");

		int year = 1954;
		UTest::AssertEqual(person.GetFullName(year), "Thornton" + append, "GetFullName(" + std::to_string(year) + ")");
		year = 1964;
		UTest::AssertEqual(person.GetFullName(year), "Mills" + append, "GetFullName(" + std::to_string(year) + ")");
	}
}

void Person_WhenCalledGetFullName_ReturnsFullName() {
	Person person {};

	{
		person.ChangeFirstName(1955, "David");
		person.ChangeLastName(1953, "Thornton");

		int year = 1966;
		UTest::AssertEqual(person.GetFullName(year), "David Thornton", "GetFullName(" + std::to_string(year) + ")");
	}

	{
		person.ChangeFirstName(1965, "George");
		person.ChangeLastName(1963, "Mills");

		int year = 1960;
		UTest::AssertEqual(person.GetFullName(year), "David Thornton", "GetFullName(" + std::to_string(year) + ")");
		year = 1964;
		UTest::AssertEqual(person.GetFullName(year), "David Mills", "GetFullName(" + std::to_string(year) + ")");
		year = 1967;
		UTest::AssertEqual(person.GetFullName(year), "George Mills", "GetFullName(" + std::to_string(year) + ")");
	}
}

/*  End Tests  */

void RunAllTests() {
	UTest::TestRunner tr {};

	std::vector<std::pair<std::string, std::function<void()>>> listOfFunctions {
		{ "Person_WhenCalledGetFullName_ReturnsIncognito", Person_WhenCalledGetFullName_ReturnsIncognito },
		{ "Person_WhenCalledGetFullName_ReturnsFirstName",  Person_WhenCalledGetFullName_ReturnsFirstName },
		{ "Person_WhenCalledGetFullName_ReturnsLastName",  Person_WhenCalledGetFullName_ReturnsLastName },
		{ "Person_WhenCalledGetFullName_ReturnsFullName",  Person_WhenCalledGetFullName_ReturnsFullName },
	};

	for (auto& item : listOfFunctions) {
		tr.RunTest(item.second, item.first);
	}
}

int main() {
	RunAllTests();

	return 0;
}
