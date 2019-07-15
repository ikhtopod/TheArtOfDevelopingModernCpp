#include <cstdlib>
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
	for (const auto& [key, value] : rhs) {
		if (first) {
			first = false;
		} else {
			lhs << ", ";
		}//fi

		lhs << key << ": " << value;
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

#pragma region GetDistinctRealRootCount
template <typename T>
T ToSquare(T x) {
	return x * x;
}

template <typename T>
T GetDiscriminant(T a, T b, T c) {
	return ToSquare(b) - (4 * a * c);
}

int GetDistinctRealRootCount(double a, double b, double c) {
	if (a != 0 && b != 0 && c != 0) {
		double d = GetDiscriminant(a, b, c);

		if (d > 0) {
			return 2;
		} else if (d == 0) {
			return 1;
		} else {
			return 0;
		}//fi
	} else if (a == 0 && b != 0 && c != 0) {
		return 1;
	} else if (a != 0 && b != 0 && c == 0) {
		return 2;
	} else if (a != 0 && b == 0 && c == 0) {
		return 2;
	} else if (a == 0 && b != 0 && c == 0) {
		return 1;
	}//fi

	return 0;
}
#pragma endregion GetDistinctRealRootCount

namespace UTest = ru::lifanoff::utest;

/* Begin Tests */

void GetDistinctRealRootCount_Test1() {
	UTest::AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0, R"test("Test 1: GetDistinctRealRootCount(0, 0, 1)")test");
	UTest::AssertEqual(GetDistinctRealRootCount(0, 1, 0), 1, R"test("Test 1: GetDistinctRealRootCount(0, 1, 0)")test");
	UTest::AssertEqual(GetDistinctRealRootCount(1, 0, 0), 1, R"test("Test 1: GetDistinctRealRootCount(1, 0, 0)")test");
}

void GetDistinctRealRootCount_Test2() {
	UTest::AssertEqual(GetDistinctRealRootCount(1, 0, 1), 0, R"test("Test 2: GetDistinctRealRootCount(1, 0, 1)")test");
	UTest::AssertEqual(GetDistinctRealRootCount(0, 1, 1), 1, R"test("Test 2: GetDistinctRealRootCount(0, 1, 1)")test");
	UTest::AssertEqual(GetDistinctRealRootCount(1, 1, 0), 2, R"test("Test 2: GetDistinctRealRootCount(1, 1, 0)")test");
}

void GetDistinctRealRootCount_Test3() {
	UTest::AssertEqual(GetDistinctRealRootCount(1, 1, 1), 0, R"test("Test 3: GetDistinctRealRootCount(1, 1, 1)")test");
	UTest::AssertEqual(GetDistinctRealRootCount(6, 23, 89), 0, R"test("Test 3: GetDistinctRealRootCount(6, 23, 89)")test");
	UTest::AssertEqual(GetDistinctRealRootCount(58, 19, 66), 0, R"test("Test 3: GetDistinctRealRootCount(58, 19, 66)")test");
}

void GetDistinctRealRootCount_Test4() {
	UTest::AssertEqual(GetDistinctRealRootCount(2, 4, 2), 1, R"test("Test 4: GetDistinctRealRootCount(2, 4, 2)")test");
	UTest::AssertEqual(GetDistinctRealRootCount(0, 4, 3), 1, R"test("Test 4: GetDistinctRealRootCount(0, 4, 3)")test");
	UTest::AssertEqual(GetDistinctRealRootCount(0, 77, 0), 1, R"test("Test 4: GetDistinctRealRootCount(0, 77, 0)")test");
}

void GetDistinctRealRootCount_Test5() {
	UTest::AssertEqual(GetDistinctRealRootCount(-36, -26, 14), 2, R"test("Test 5: GetDistinctRealRootCount(-36, 26, 14)")test");
	UTest::AssertEqual(GetDistinctRealRootCount(-6, 23, 89), 2, R"test("Test 5: GetDistinctRealRootCount(-6, 23, 89)")test");
	UTest::AssertEqual(GetDistinctRealRootCount(17, 71, -56), 2, R"test("Test 5: GetDistinctRealRootCount(17, 71, -56)")test");
}


/*  End Tests  */

void RunAllTests() {
	UTest::TestRunner tr {};

	std::map<std::string, std::function<void()>> listOfFunctions {
		{ "GetDistinctRealRootCount_Test1", GetDistinctRealRootCount_Test1 },
		{ "GetDistinctRealRootCount_Test2", GetDistinctRealRootCount_Test2 },
		{ "GetDistinctRealRootCount_Test3", GetDistinctRealRootCount_Test3 },
		{ "GetDistinctRealRootCount_Test4", GetDistinctRealRootCount_Test4 },
		{ "GetDistinctRealRootCount_Test5", GetDistinctRealRootCount_Test5 },
	};

	for (auto& [funcName, func] : listOfFunctions) {
		tr.RunTest(func, funcName);
	}
}

int main() {
	RunAllTests();

	return 0;
}