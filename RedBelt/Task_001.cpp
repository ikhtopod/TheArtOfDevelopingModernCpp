#include "test_runner.h"

#include <string>
#include <vector>
#include <list>
#include <forward_list>
#include <numeric>
#include <iterator>
#include <algorithm>

using namespace std;

#ifdef RU_LIFANOFF_UTEST_TEST_RUNNER_H
using namespace ru::lifanoff::utest;
#endif // RU_LIFANOFF_UTEST_TEST_RUNNER_H

template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred) {
	ForwardIterator result = last;

	for (auto it = first; it != last; std::advance(it, 1)) {
		if (pred(*it) && (result == last || *result > *it)) {
			result = it;
		}
	}

	return result;
}

void TestUniqueMax() {
	auto IsEven = [](int x) {
		return x % 2 == 0;
	};

	const list<int> hill { 2, 4, 8, 9, 6, 4, 2 };
	auto max_iterator = hill.begin();
	advance(max_iterator, 2);

	vector<int> numbers(10);
	iota(numbers.begin(), numbers.end(), 1);

	/*
	  �� �� ���������� AssertEqual, ������ ��� ��� ����������
	  ����������� ���������� ��������� ������ � ����� ostream.
	  ������������� ����� ����� �����������, ��� ��� ��� ����� �������
	  �������������� ���������, ���� ������� max_element_if, � �������,
	  ������� ��������, ����������� �� ����� ����������.
	*/
	ASSERT(max_element_if(numbers.begin(), numbers.end(), IsEven) == --numbers.end());
	ASSERT(max_element_if(hill.begin(), hill.end(), IsEven) == max_iterator);
}

void TestSeveralMax() {
	struct IsCapitalized {
		bool operator()(const string& s) {
			return !s.empty() && isupper(s.front());
		}
	};

	const forward_list<string> text { "One", "two", "Three", "One", "Two",
	  "Three", "one", "Two", "three" };
	auto max_iterator = text.begin();
	advance(max_iterator, 4);

	ASSERT(max_element_if(text.begin(), text.end(), IsCapitalized()) == max_iterator);
}

void TestNoMax() {
	const vector<int> empty;
	const string str = "Non-empty string";

	auto AlwaysTrue = [](int) {
		return true;
	};
	ASSERT(max_element_if(empty.begin(), empty.end(), AlwaysTrue) == empty.end());

	auto AlwaysFalse = [](char) {
		return false;
	};
	ASSERT(max_element_if(str.begin(), str.end(), AlwaysFalse) == str.end());
}

int main() {
	TestRunner tr;
	TEST_RUN(tr, TestUniqueMax);
	TEST_RUN(tr, TestSeveralMax);
	TEST_RUN(tr, TestNoMax);
	return 0;
}
