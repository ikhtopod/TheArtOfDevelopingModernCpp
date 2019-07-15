#include <cstdlib>
#include <random>
#include <chrono>
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

/**
	\code
		RandomYearGenerator ryg { 1700, 2019 };
		int year = ryg.GetRandomYear();
	\endcode
*/
class RandomYearGenerator final {
private:
	inline static const int DEFAULT_MIN_YEAR = 0;
	inline static const int DEFAULT_MAX_YEAR = 2019;

private:
	uint32_t m_seed = 0;

	int m_minYear = DEFAULT_MIN_YEAR;
	int	m_maxYear = DEFAULT_MAX_YEAR;

	std::default_random_engine m_dre { m_seed };
	std::uniform_int_distribution<int> m_uid { m_minYear, m_maxYear };

	int m_year = DEFAULT_MIN_YEAR;

private:
	static uint32_t GenerateSeed() {
		using namespace std::chrono;

		time_point<steady_clock> nowTime = steady_clock::now();
		long long year = nowTime.time_since_epoch().count();
		return static_cast<uint32_t>(year);
	}

public:
	RandomYearGenerator() :
		RandomYearGenerator(DEFAULT_MIN_YEAR, DEFAULT_MAX_YEAR) {}

	RandomYearGenerator(int minYear, int maxYear) :
		RandomYearGenerator(GenerateSeed(), minYear, maxYear) {}

	RandomYearGenerator(uint32_t seed, int minYear, int maxYear) :
		m_seed(seed), m_minYear(minYear), m_maxYear(maxYear),
		m_dre(m_seed), m_uid(m_minYear, m_maxYear) {}

	int GetRandomYear() {
		m_year = m_uid(m_dre);
		return GetLastYear();
	}

	int GetLastYear() {
		return m_year;
	}
};

}//! namespace ru::lifanoff::utest

#pragma endregion


namespace ns_UTest = ru::lifanoff::utest;

int Sum(int x, int y) { return x + y; }

void Sum_Test1() {
	ns_UTest::AssertEqual(Sum(2, 3), 5, "Sum(2, 3), 5");
	ns_UTest::AssertEqual(Sum(-2, -3), -5, "Sum(-2, -3), -5");
	ns_UTest::AssertEqual(Sum(-2, 0), -2, "Sum(-2, 0), -2");
	ns_UTest::AssertEqual(Sum(-2, 2), 0, "Sum(-2, 2), 0");
}
void Sum_Test2() {
	ns_UTest::AssertEqual(Sum(2, 3), 5, "Sum(2, 3), 5");
	ns_UTest::AssertEqual(Sum(-2, -3), -5, "Sum(-2, -3), -5");
	ns_UTest::AssertEqual(Sum(-2, 0), -2, "Sum(-2, 0), -2");
	ns_UTest::AssertEqual(Sum(-2, 2), 0, "Sum(-2, 2), 0");
	ns_UTest::AssertEqual(Sum(-2, 0), 2, "Sum(-2, 0), 2"); // wrong
}

void Sum_Test3() {
	ns_UTest::Assert(Sum(2, 3) == Sum(3, 2), "Sum(2, 3) == Sum(3, 2)");
	ns_UTest::Assert(Sum(-2, 3) != Sum(-3, 2), "Sum(-2, 3) != Sum(-3, 2)");
	ns_UTest::Assert(Sum(-2, 3) == Sum(-3, 2), "Sum(-2, 3) != Sum(-3, 2)"); // wrong
	ns_UTest::Assert(Sum(2, 4) == Sum(Sum(1, 1), Sum(2, 2)),
					 "Sum(2, 4) == Sum(Sum(1, 1), Sum(2, 2)");
}

void Sum_Test4() {
	{
		std::map<std::string, std::set<size_t>> m1 {};
		std::map<std::string, std::set<size_t>> m2 {};

		ns_UTest::AssertEqual(m1, m2, "1");
		ns_UTest::Assert(m1.empty() && m2.empty(), "2");
	}
	{
		std::map<std::string, std::set<size_t>> m3 {
			{"random numbers", { 1, 6, 3, 7, 3, 8, 5, 14, 12, 18, 14, 5, 7 }},
			{"shuffle unique fibonacci", { 0, 1, 2, 3, 5, 89, 8, 13, 34, 34, 89, 21, 1, 55 }},
		};

		std::map<std::string, std::set<size_t>> m4 {
			{"random numbers", { 1, 6, 3, 7, 3, 8, 5, 14, 12, 18, 14, 5, 7 }},
			{"shuffle unique fibonacci", { 0, 1, 2, 3, 5, 89, 8, 13, 34, 34, 89, 21, 1, 55 }},
		};

		ns_UTest::AssertEqual(m3, m4, "3");
		ns_UTest::Assert(!(m3.empty() && m4.empty()), "4");
	}
	{
		std::map<std::string, std::set<size_t>> m3 {
			{"random numbers", { 1, 6, 3, 7, 3, 8, 5, 14, 12, 18, 14, 5, 7 }},
			{"shuffle unique fibonacci", { 0, 1, 2, 3, 5, 89, 8, 13, 34, 34, 89, 21, 1, 55 }},
		};

		std::map<std::string, std::set<size_t>> m4 {
			{"random numbers", { 1, 6, 3, 7, 3, 7, 8, 5, 12, 18, 14, 5, 5 }},
			{"shuffle unique fibonacci", { 5, 89, 3, 8, 2, 1, 13, 1, 34, 0, 34, 89, 21, 1, 3, 55 }},
		};

		ns_UTest::AssertEqual(m3, m4, "5");
		ns_UTest::Assert(!(m3.empty() && m4.empty()), "6");
	}

	{// wrong
		std::map<std::string, std::set<size_t>> m3 {
			{"random numbers", { 1, 6, 3, 7, 3, 8, 5, 14, 12, 18, 14, 5, 7 }},
			{"shuffle unique fibonacci", { 0, 1, 2, 3, 5, 89, 8, 13, 34, 34, 89, 21, 1, 55 }},
		};

		std::map<std::string, std::set<size_t>> m4 {
			{"random numbers", { 1, 6, 3, 7, 3, 7, 5, 12, 18, 14, 5, 5 }},
			{"shuffle unique fibonacci", { 5, 89, 3, 8, 2, 1, 13, 1, 34, 0, 34, 89, 21, 1, 3, 55 }},
		};

		ns_UTest::AssertEqual(m3, m4, "7");
		ns_UTest::Assert(!(m3.empty() && m4.empty()), "8");
	}// wrong
}

void Sum_Test5() {
	{
		std::map<std::string, std::vector<size_t>> m1 {};
		std::map<std::string, std::vector<size_t>> m2 {};

		ns_UTest::AssertEqual(m1, m2, "1");
		ns_UTest::Assert(m1.empty() && m2.empty(), "2");
	}
	{
		std::map<std::string, std::vector<size_t>> m3 {
			{"random numbers", { 1, 6, 3, 7, 3, 8, 5, 14, 12, 18, 14, 5, 7 }},
			{"shuffle unique fibonacci", { 0, 1, 2, 3, 5, 89, 8, 13, 34, 34, 89, 21, 1, 55 }},
		};

		std::map<std::string, std::vector<size_t>> m4 {
			{"random numbers", { 1, 6, 3, 7, 3, 8, 5, 14, 12, 18, 14, 5, 7 }},
			{"shuffle unique fibonacci", { 0, 1, 2, 3, 5, 89, 8, 13, 34, 34, 89, 21, 1, 55 }},
		};

		ns_UTest::AssertEqual(m3, m4, "3");
		ns_UTest::Assert(!(m3.empty() && m4.empty()), "4");
	}
	{// wrong
		std::map<std::string, std::vector<size_t>> m3 {
			{"random numbers", { 1, 2, 3 }},
			{"shuffle unique fibonacci", { 0, 1, 1 }},
		};

		std::map<std::string, std::vector<size_t>> m4 {
			{"random numbers", { 0, 1, 1 }},
			{"shuffle unique fibonacci", { 1, 2, 3 }},
		};

		ns_UTest::AssertEqual(m3, m4, "7");
		ns_UTest::Assert(!(m3.empty() && m4.empty()), "8");
	}// wrong
}

void Sum_Test6() {
	{
		std::string strP1 { "" };
		std::pair<std::string, size_t> p1 { strP1, strP1.size() };

		std::string strP2 { "" };
		std::pair<std::string, size_t> p2 { strP2, strP2.size() };

		ns_UTest::AssertEqual(p1, p2, "1");
	}
	{
		std::string strP1 { "Hello" };
		std::pair<std::string, size_t> p1 { strP1, strP1.size() };

		std::string strP2 { "Hello" };
		std::pair<std::string, size_t> p2 { strP2, strP2.size() };

		ns_UTest::AssertEqual(p1, p2, "2");
	}
	{// wrong
		std::string strP1 { "Hello" };
		std::pair<std::string, size_t> p1 { strP1, strP1.size() };

		std::string strP2 { "Howdy" };
		std::pair<std::string, size_t> p2 { strP2, strP2.size() };

		ns_UTest::AssertEqual(p1, p2, "3");
	}// wrong
}

void RunAllTests() {
	ns_UTest::TestRunner tr {};

	tr.RunTest(Sum_Test1, "Sum_Test1");
	tr.RunTest(Sum_Test2, "Sum_Test2");
	tr.RunTest(Sum_Test3, "Sum_Test3");
	tr.RunTest(Sum_Test4, "Sum_Test4");
	tr.RunTest(Sum_Test5, "Sum_Test5");
	tr.RunTest(Sum_Test6, "Sum_Test6");
}

int main() {
	RunAllTests();

	return EXIT_SUCCESS;
}
