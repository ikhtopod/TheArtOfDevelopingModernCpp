#pragma once

#ifndef COURSERAUNITTEST_TEST_RUNNER_H
#define COURSERAUNITTEST_TEST_RUNNER_H

#include <cstdlib>
#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>
#include <map>
#include <set>


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

void Assert(bool b, const std::string& hint);


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
		oss << "Assertion failed: " << t << " != " << u
			<< ". Hint: " << hint;
		throw std::runtime_error { oss.str() };
	}//fi
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

#define INSERT_PREFIX(counter) id ## counter
#define MAKE_ID(counter) INSERT_PREFIX(counter)
#define UNIQ_ID MAKE_ID(__COUNTER__)

#define ASSERT_EQUAL_ID(uniq_id_name, x, y) {		\
	std::ostringstream uniq_id_name {};				\
	uniq_id_name << #x << " != " << #y << ", " <<	\
		__FILE__ << ":" << __LINE__;				\
	AssertEqual(x, y, uniq_id_name.str());			\
}

#define ASSERT_ID(uniq_id_name, x) {				\
	std::ostringstream uniq_id_name {};				\
	uniq_id_name << '!' << #x << ", " <<			\
		__FILE__ << ":" << __LINE__;				\
	Assert(x, uniq_id_name.str());					\
}

#define ASSERT_EQUAL(x, y) ASSERT_EQUAL_ID(UNIQ_ID, x, y) 
#define ASSERT(x) ASSERT_ID(UNIQ_ID, x)

#define INIT_TEST_RUNNER TestRunner tr {}
#define RUN_TEST(tr, func) tr.RunTest(func, #func)


#endif // !COURSERAUNITTEST_TEST_RUNNER_H
