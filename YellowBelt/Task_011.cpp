#include <cstdlib>
#include <cmath>
#include <limits>
#include <random>
#include <chrono>
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

using namespace std::rel_ops;

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


#pragma region Rational
//using namespace std;

class Rational {
private:
	int m_numerator = 0;
	int m_denominator = 1;

private:
	int getGcd() {
		int a = std::abs(m_numerator);
		int b = std::abs(m_denominator);

		while (b != 0) {
			int tmp = a;
			a = b;
			b = tmp % b;
		}

		return a;
	}

	void reduceFraction() {
		for (int gcd = getGcd(); gcd != 1; gcd = getGcd()) {
			m_numerator /= gcd;
			m_denominator /= gcd;
		}
	}

	void normalize() {
		if (m_numerator == 0) {
			m_denominator = 1;
		} else if (m_numerator < 0 && m_denominator < 0) {
			m_numerator = std::abs(m_numerator);
			m_denominator = std::abs(m_denominator);
		} else if (m_numerator < 0 || m_denominator < 0) {
			m_numerator = -std::abs(m_numerator);
			m_denominator = std::abs(m_denominator);
		}//fi

		reduceFraction();
	}

public:
	Rational() : Rational(0, 1) {}

	Rational(int numerator, int denominator) {
		m_numerator = numerator;
		m_denominator = denominator;

		normalize();
	}

	int Numerator() const {
		return m_numerator;
	}

	int Denominator() const {
		return m_denominator;
	}
};
#pragma endregion Rational

#pragma region RationalForRandomTest
class RationalForRandomTest {
private:
	int m_numerator = 0;
	int m_denominator = 1;

private:
	int getGcd() {
		int a = std::abs(m_numerator);
		int b = std::abs(m_denominator);

		while (b != 0) {
			int tmp = a;
			a = b;
			b = tmp % b;
		}

		return a;
	}

	void reduceFraction() {
		for (int gcd = getGcd(); gcd != 1; gcd = getGcd()) {
			m_numerator /= gcd;
			m_denominator /= gcd;
		}
	}

	void normalize() {
		if (m_numerator == 0) {
			m_denominator = 1;
		} else if (m_numerator < 0 && m_denominator < 0) {
			m_numerator = std::abs(m_numerator);
			m_denominator = std::abs(m_denominator);
		} else if (m_numerator < 0 || m_denominator < 0) {
			m_numerator = -std::abs(m_numerator);
			m_denominator = std::abs(m_denominator);
		}//fi

		reduceFraction();
	}

public:
	RationalForRandomTest() : RationalForRandomTest(0, 1) {}

	RationalForRandomTest(int numerator, int denominator) {
		m_numerator = numerator;
		m_denominator = denominator;

		normalize();
	}

	int Numerator() const {
		return m_numerator;
	}

	int Denominator() const {
		return m_denominator;
	}
};
#pragma endregion RationalForRandomTest

namespace UTest = ru::lifanoff::utest;

#pragma region Tests

void Rational_Creates_DefaultConstructor() {
	Rational r {};

	const std::string hint { R"*(Rational {})*" };
	const std::string hintNumerator { hint + " for Numerator" };
	const std::string hintDenominator { hint + " for Denominator" };

	UTest::AssertEqual(r.Numerator(), 0, hintNumerator);
	UTest::AssertEqual(r.Denominator(), 1, hintDenominator);
}

void Rational_Creates_CustomConstructor() {
	{
		Rational r { 0, 1 };

		const std::string hint { R"*(Rational { 0, 1 })*" };
		const std::string hintNumerator { hint + " for Numerator" };
		const std::string hintDenominator { hint + " for Denominator" };

		UTest::AssertEqual(r.Numerator(), 0, hintNumerator);
		UTest::AssertEqual(r.Denominator(), 1, hintDenominator);
	}

	{
		Rational r { 0, 50 };

		const std::string hint { R"*(Rational { 0, 50 })*" };
		const std::string hintNumerator { hint + " for Numerator" };
		const std::string hintDenominator { hint + " for Denominator" };

		UTest::AssertEqual(r.Numerator(), 0, hintNumerator);
		UTest::AssertEqual(r.Denominator(), 1, hintDenominator);
	}

	{
		Rational r { 1, 50 };

		const std::string hint { R"*(Rational { 1, 50 })*" };
		const std::string hintNumerator { hint + " for Numerator" };
		const std::string hintDenominator { hint + " for Denominator" };

		UTest::AssertEqual(r.Numerator(), 1, hintNumerator);
		UTest::AssertEqual(r.Denominator(), 50, hintDenominator);
	}

	{
		Rational r { 17, 33 };

		const std::string hint { R"*(Rational { 17, 33 })*" };
		const std::string hintNumerator { hint + " for Numerator" };
		const std::string hintDenominator { hint + " for Denominator" };

		UTest::AssertEqual(r.Numerator(), 17, hintNumerator);
		UTest::AssertEqual(r.Denominator(), 33, hintDenominator);
	}
}

void Rational_Performs_ReduceFraction() {
	{
		Rational r { 2, 4 };

		const std::string hint { R"*(Rational { 2, 4 })*" };
		const std::string hintNumerator { hint + " for Numerator" };
		const std::string hintDenominator { hint + " for Denominator" };

		UTest::AssertEqual(r.Numerator(), 1, hintNumerator);
		UTest::AssertEqual(r.Denominator(), 2, hintDenominator);
	}

	{
		Rational r { 38, 54 };

		const std::string hint { R"*(Rational { 38, 54 })*" };
		const std::string hintNumerator { hint + " for Numerator" };
		const std::string hintDenominator { hint + " for Denominator" };

		UTest::AssertEqual(r.Numerator(), 19, hintNumerator);
		UTest::AssertEqual(r.Denominator(), 27, hintDenominator);
	}

	{
		Rational r { 1'000'000, 500'000 };

		const std::string hint { R"*(Rational { 1'000'000, 500'000 })*" };
		const std::string hintNumerator { hint + " for Numerator" };
		const std::string hintDenominator { hint + " for Denominator" };

		UTest::AssertEqual(r.Numerator(), 2, hintNumerator);
		UTest::AssertEqual(r.Denominator(), 1, hintDenominator);
	}
}

void Rational_CreatesConstructor_WithNegativeValues() {
	{
		Rational r { 0, -1 };

		const std::string hint { R"*(Rational { 0, -1 })*" };
		const std::string hintNumerator { hint + " for Numerator" };
		const std::string hintDenominator { hint + " for Denominator" };

		UTest::AssertEqual(r.Numerator(), 0, hintNumerator);
		UTest::AssertEqual(r.Denominator(), 1, hintDenominator);
	}

	{
		Rational r { 0, -50 };

		const std::string hint { R"*(Rational { 0, -50 })*" };
		const std::string hintNumerator { hint + " for Numerator" };
		const std::string hintDenominator { hint + " for Denominator" };

		UTest::AssertEqual(r.Numerator(), 0, hintNumerator);
		UTest::AssertEqual(r.Denominator(), 1, hintDenominator);
	}

	{
		Rational r { -1, -50 };

		const std::string hint { R"*(Rational { -1, -50 })*" };
		const std::string hintNumerator { hint + " for Numerator" };
		const std::string hintDenominator { hint + " for Denominator" };

		UTest::AssertEqual(r.Numerator(), 1, hintNumerator);
		UTest::AssertEqual(r.Denominator(), 50, hintDenominator);
	}

	{
		Rational r { -17, 33 };

		const std::string hint { R"*(Rational { 17, 33 })*" };
		const std::string hintNumerator { hint + " for Numerator" };
		const std::string hintDenominator { hint + " for Denominator" };

		UTest::AssertEqual(r.Numerator(), -17, hintNumerator);
		UTest::AssertEqual(r.Denominator(), 33, hintDenominator);
	}

	{
		Rational r { 23, -31 };

		const std::string hint { R"*(Rational { 23, -31 })*" };
		const std::string hintNumerator { hint + " for Numerator" };
		const std::string hintDenominator { hint + " for Denominator" };

		UTest::AssertEqual(r.Numerator(), -23, hintNumerator);
		UTest::AssertEqual(r.Denominator(), 31, hintDenominator);
	}

	{
		Rational r { 2, -4 };

		const std::string hint { R"*(Rational { 2, 4 })*" };
		const std::string hintNumerator { hint + " for Numerator" };
		const std::string hintDenominator { hint + " for Denominator" };

		UTest::AssertEqual(r.Numerator(), -1, hintNumerator);
		UTest::AssertEqual(r.Denominator(), 2, hintDenominator);
	}

	{
		Rational r { -38, -54 };

		const std::string hint { R"*(Rational { 38, 54 })*" };
		const std::string hintNumerator { hint + " for Numerator" };
		const std::string hintDenominator { hint + " for Denominator" };

		UTest::AssertEqual(r.Numerator(), 19, hintNumerator);
		UTest::AssertEqual(r.Denominator(), 27, hintDenominator);
	}

	{
		Rational r { -1'000'000, 500'000 };

		const std::string hint { R"*(Rational { 1'000'000, 500'000 })*" };
		const std::string hintNumerator { hint + " for Numerator" };
		const std::string hintDenominator { hint + " for Denominator" };

		UTest::AssertEqual(r.Numerator(), -2, hintNumerator);
		UTest::AssertEqual(r.Denominator(), 1, hintDenominator);
	}
}

void Rational_RandomTest() {
	using namespace std::chrono;

	time_point<steady_clock> timeNow = steady_clock::now();
	nanoseconds timeEpoch = timeNow.time_since_epoch();
	uint32_t seed = static_cast<uint32_t>(duration_cast<milliseconds>(timeEpoch).count());
	std::default_random_engine dre { seed };
	std::uniform_int_distribution<int> uid { std::numeric_limits<int>::min(), std::numeric_limits<int>::max() };

	for (int i = 0; i < 500; ++i) {
		int numerator = uid(dre);
		int denominator = uid(dre);

		Rational r { numerator, denominator };
		RationalForRandomTest rTest { numerator, denominator };

		const std::string hint { "Rational { " + std::to_string(numerator) + ", " +
			std::to_string(denominator) + " }" };
		const std::string hintNumerator { hint + " for Numerator" };
		const std::string hintDenominator { hint + " for Denominator" };

		UTest::AssertEqual(r.Numerator(), rTest.Numerator(), hintNumerator);
		UTest::AssertEqual(r.Denominator(), rTest.Denominator(), hintDenominator);
	}
}

#pragma endregion Tests

void RunAllTests() {
	UTest::TestRunner tr {};

	std::vector<std::pair<std::string, std::function<void()>>> listOfFunctions {
		{ "Rational_Creates_DefaultConstructor", Rational_Creates_DefaultConstructor },
		{ "Rational_Creates_CustomConstructor", Rational_Creates_CustomConstructor },
		{ "Rational_Performs_ReduceFraction", Rational_Performs_ReduceFraction },
		{ "Rational_CreatesConstructor_WithNegativeValues", Rational_CreatesConstructor_WithNegativeValues },
		{ "Rational_RandomTest", Rational_RandomTest },
	};

	for (auto& item : listOfFunctions) {
		tr.RunTest(item.second, item.first);
	}
}

int main() {
	RunAllTests();

	return 0;
}
