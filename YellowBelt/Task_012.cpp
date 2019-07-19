#include "test_runner.h"

#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <cassert>
#include <stdexcept>
#include <utility>
#include <vector>


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
