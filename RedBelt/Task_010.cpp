#include "student.h"
#include "test_runner.h"
#include "profile.h"

#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

//Оптимизируйте эту функцию
bool Compare(const Student& first, const Student& second) {
	return first.Less(second);
}

bool CompareOld(Student first, Student second) {
	return first.Less(second);
}

void TestComparison() {
	Student newbie {
	  "Ivan", "Ivanov", {
		{"c++", 1.0},
		{"algorithms", 3.0}
	  },
	  2.0
	};

	Student cpp_expert {
	  "Petr", "Petrov", {
		{"c++", 9.5},
		{"algorithms", 6.0}
	  },
	  7.75
	};

	Student guru {
	  "Sidor", "Sidorov", {
		{"c++", 10.0},
		{"algorithms", 10.0}
	  },
	  10.0
	};
	ASSERT(Compare(guru, newbie));
	ASSERT(Compare(guru, cpp_expert));
	ASSERT(!Compare(newbie, cpp_expert));
}

void TestSorting() {
	vector<Student> students {
	  {"Sidor", "Sidorov", {{"maths", 2.}}, 2.},
	  {"Semen", "Semenov", {{"maths", 4.}}, 4.},
	  {"Ivan", "Ivanov", {{"maths", 5.}}, 5.},
	  {"Petr", "Petrov", {{"maths", 3.}}, 3.},
	  {"Alexander", "Alexandrov", {{"maths", 1.}}, 1.}
	};
	sort(students.begin(), students.end(), Compare);
	ASSERT(is_sorted(students.begin(), students.end(),
		   [](Student first, Student second) {
			   return first.Less(second);
		   })
	);
}

void TestRandomDuration() {
	LOG_DURATION("");

	using namespace std::chrono;

	uint32_t seed = duration_cast<duration<uint32_t, milli>>(steady_clock::now().time_since_epoch()).count();
	default_random_engine dre { seed };
	uniform_real_distribution<double> urd { 0.0, 5.0 };

	vector<Student> students {};
	string studentName { "abcdefgh" };

	double mark = urd(dre);
	do {
		students.push_back({ studentName, studentName + "ov", {{"maths", mark}}, mark });
	} while (next_permutation(studentName.begin(), studentName.end()));

	sort(students.begin(), students.end(), Compare);
	ASSERT(is_sorted(students.begin(), students.end(),
		   [](Student first, Student second) {
			   return first.Less(second);
		   })
	);
}

void TestRandomDurationOld() {
	LOG_DURATION("");

	using namespace std::chrono;

	uint32_t seed = duration_cast<duration<uint32_t, milli>>(steady_clock::now().time_since_epoch()).count();
	default_random_engine dre { seed };
	uniform_real_distribution<double> urd { 0.0, 5.0 };

	vector<Student> students {};
	string studentName { "ijklmnop" };

	double mark = urd(dre);
	do {
		students.push_back({ studentName, studentName + "ov", {{"maths", mark}}, mark });
	} while (next_permutation(studentName.begin(), studentName.end()));

	sort(students.begin(), students.end(), CompareOld);
	ASSERT(is_sorted(students.begin(), students.end(),
		   [](Student first, Student second) {
			   return first.Less(second);
		   })
	);
}


int main() {
	TestRunner tr;
	RUN_TEST(tr, TestComparison);
	RUN_TEST(tr, TestSorting);
	RUN_TEST(tr, TestRandomDurationOld);
	RUN_TEST(tr, TestRandomDuration);
	return 0;
}
