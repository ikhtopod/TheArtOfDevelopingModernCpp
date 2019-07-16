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


#pragma region IsPalindrom

bool IsPalindrom(const std::string& str) {
	if (str.empty()) return true;

	for (size_t i = 0, j = str.size() - 1; i < j; ++i, --j) {
		if (str[i] != str[j]) {
			return false;
		}//fi
	}//rof

	return true;
}

#pragma endregion IsPalindrom


namespace UTest = ru::lifanoff::utest;


#pragma region Tests

void IsPalindrom_Called_WithEmptyString() {
	{
		std::string str {};

		UTest::Assert(IsPalindrom(str), "IsPalindrom(" + str + ")");
	}
}

void IsPalindrom_Called_WithSingleString() {
	{
		std::string str { "X" };

		UTest::Assert(IsPalindrom(str), "IsPalindrom(" + str + ")");
	}
}

void IsPalindrom_Called_WithCorrectPalindrom() {
	{
		std::string str { "madam" };

		UTest::Assert(IsPalindrom(str), "IsPalindrom(" + str + ")");
	}

	{
		std::string str { "okololoko" };

		UTest::Assert(IsPalindrom(str), "IsPalindrom(" + str + ")");
	}

	{
		std::string str { "esse" };

		UTest::Assert(IsPalindrom(str), "IsPalindrom(" + str + ")");
	}
}

void IsPalindrom_Called_WithNotCorrectPalindrom() {
	{
		std::string str { "gentleman" };

		UTest::Assert(!IsPalindrom(str), "IsPalindrom(" + str + ")");
	}

	{
		std::string str { "batat" };

		UTest::Assert(!IsPalindrom(str), "IsPalindrom(" + str + ")");
	}

	{
		std::string str { " madam" };

		UTest::Assert(!IsPalindrom(str), "IsPalindrom(" + str + ")");
	}

	{
		std::string str { "madam " };

		UTest::Assert(!IsPalindrom(str), "IsPalindrom(" + str + ")");
	}

	{
		std::string str { "adam" };

		UTest::Assert(!IsPalindrom(str), "IsPalindrom(" + str + ")");
	}

	{
		std::string str { "messe" };

		UTest::Assert(!IsPalindrom(str), "IsPalindrom(" + str + ")");
	}

	{
		std::string str { "messes" };

		UTest::Assert(!IsPalindrom(str), "IsPalindrom(" + str + ")");
	}


	{
		std::string str { "abcdba" };

		UTest::Assert(!IsPalindrom(str), "IsPalindrom(" + str + ")");
	}
}

#pragma endregion Tests


void RunAllTests() {
	UTest::TestRunner tr {};

	std::vector<std::pair<std::string, std::function<void()>>> listOfFunctions {
		{ "IsPalindrom_Called_WithEmptyString", IsPalindrom_Called_WithEmptyString },
		{ "IsPalindrom_Called_WithSingleString", IsPalindrom_Called_WithSingleString },
		{ "IsPalindrom_Called_WithCorrectPalindrom", IsPalindrom_Called_WithCorrectPalindrom },
		{ "IsPalindrom_Called_WithNotCorrectPalindrom", IsPalindrom_Called_WithNotCorrectPalindrom },
	};

	for (auto& item : listOfFunctions) {
		tr.RunTest(item.second, item.first);
	}
}

int main() {
	RunAllTests();

	return 0;
}
