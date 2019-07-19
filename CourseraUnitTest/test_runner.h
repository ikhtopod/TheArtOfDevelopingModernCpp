#pragma once

#ifndef ru_LIFANOFF_UTEST_TEST_RUNNER_H
#define ru_LIFANOFF_UTEST_TEST_RUNNER_H

#include <cstdlib>
#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>
#include <map>
#include <set>

namespace ru::lifanoff::utest {


template <class Value>
std::ostream& operator<<(std::ostream& lhs, const std::vector<Value>& rhs);

template <class Value>
std::ostream& operator<<(std::ostream& lhs, const std::set<Value>& rhs);

template <class First, class Second>
std::ostream& operator<<(std::ostream& lhs, const std::pair<First, Second>& rhs);

template <class Key, class Value>
std::ostream& operator<<(std::ostream& lhs, const std::map<Key, Value>& rhs);

template <class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint);

template <class T, class U>
void AssertEqual(const T& t, const U& u);

void Assert(bool b, const std::string& hint);
void Assert(bool b);


#pragma region namespace additional
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

} // !namespace additional
#pragma endregion namespace additional


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


class TestRunner final {
private:
	size_t m_failCounter = 0;

public:
	TestRunner() = default;
	~TestRunner();

	template <class TestFunc>
	void RunTest(TestFunc func, const std::string& funcName) {
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
};

}//! namespace ru::lifanoff::utest

#endif // !ru_LIFANOFF_UTEST_TEST_RUNNER_H
