#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <stdexcept>
#include <map>
#include <set>

/* Unit Test System */

namespace ru::lifanoff::utest {

template <class Key, class Value>
std::ostream& operator<<(std::ostream& lhs, const std::map<Key, Value> rhs) {
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

template <class Value>
std::ostream& operator<<(std::ostream& lhs, const std::set<Value> rhs) {
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

template <class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint) {
	if (t != u) {
		std::ostringstream oss {};
		oss << "Assertion failed: " <<
			t << " != " << u <<
			" Hint: " << hint;
		throw std::runtime_error { oss.str() };
	}//fi
}

void Assert(bool b, const std::string& hint) {
	AssertEqual(b, true, hint);
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
		std::cout << this->m_failCounter << " tests failed. Terminate";
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
	}
}

}// namespace ru::lifanoff::utest

/* Unit Test System */

namespace ns_UTest = ru::lifanoff::utest;

int Sum(int x, int y) { return x + y; }

void Sum_Test1() {
	ns_UTest::AssertEqual(Sum(2, 3), 5, "Sum(2, 3), 5");
	ns_UTest::AssertEqual(Sum(-2, -3), -5, "Sum(-2, -3), -5");
	ns_UTest::AssertEqual(Sum(-2, 0), -2, "Sum(-2, 0), -2");
	//ns_UTest::AssertEqual(Sum(-2, 0), 2, "Sum(-2, 0), 2"); // wrong
	ns_UTest::AssertEqual(Sum(-2, 2), 0, "Sum(-2, 2), 0");
}
void Sum_Test2() {
	ns_UTest::AssertEqual(Sum(2, 3), 5, "Sum(2, 3), 5");
	ns_UTest::AssertEqual(Sum(-2, -3), -5, "Sum(-2, -3), -5");
	ns_UTest::AssertEqual(Sum(-2, 0), -2, "Sum(-2, 0), -2");
	ns_UTest::AssertEqual(Sum(-2, 0), 2, "Sum(-2, 0), 2"); // wrong
	ns_UTest::AssertEqual(Sum(-2, 2), 0, "Sum(-2, 2), 0");
}

void Sum_Test3() {
	ns_UTest::Assert(Sum(2, 3) == Sum(3, 2), "Sum(2, 3) == Sum(3, 2)");
	ns_UTest::Assert(Sum(-2, 3) != Sum(-3, 2), "Sum(-2, 3) != Sum(-3, 2)");
	ns_UTest::Assert(Sum(-2, 3) == Sum(-3, 2), "Sum(-2, 3) != Sum(-3, 2)"); // wrong
	ns_UTest::Assert(Sum(2, 4) == Sum(Sum(1, 1), Sum(2, 2)),
					 "Sum(2, 4) == Sum(Sum(1, 1), Sum(2, 2)");
}

void RunAllTests() {
	ns_UTest::TestRunner tr {};

	tr.RunTest(Sum_Test1, "Sum_Test1");
	tr.RunTest(Sum_Test2, "Sum_Test2");
	tr.RunTest(Sum_Test3, "Sum_Test3");
}

int main() {
	RunAllTests();

	return EXIT_SUCCESS;
}
