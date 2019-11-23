#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <string>
#include <utility>

enum class Gender {
	FEMALE,
	MALE
};

struct Person {
	int age;  // возраст
	Gender gender;  // пол
	bool is_employed;  // имеет ли работу
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
	using namespace std;

	if (range_begin == range_end) {
		return 0;
	}

	std::vector<typename InputIt::value_type> range_copy(range_begin, range_end);

	auto middle = begin(range_copy) + range_copy.size() / 2;
	std::nth_element(
		begin(range_copy), middle, end(range_copy),
		[](const Person& lhs, const Person& rhs) {
			return lhs.age < rhs.age;
		}
	);

	return middle->age;
}

using Pred = std::function<bool(const Person& p)>;
using PairStringPred = std::pair<std::string, Pred>;
using VectorOfPairs = std::vector<PairStringPred>;

const VectorOfPairs functionsForComputing {
		{ "Median age for females = ",
			[](const Person& p) {
				return p.gender == Gender::FEMALE;
			}
		},

		{ "Median age for males = ",
			[](const Person& p) {
				return p.gender == Gender::MALE;
			}
		},

		{ "Median age for employed females = ",
			[](const Person& p) {
				return p.gender == Gender::FEMALE && p.is_employed;
			}
		},

		{ "Median age for unemployed females = ",
			[](const Person& p) {
				return p.gender == Gender::FEMALE && !p.is_employed;
			}
		},

		{ "Median age for employed males = ",
			[](const Person& p) {
				return p.gender == Gender::MALE && p.is_employed;
			}
		},

		{ "Median age for unemployed males = ",
			[](const Person& p) {
				return p.gender == Gender::MALE && !p.is_employed;
			}
		},
};

void PrintStats(std::vector<Person> persons) {
	std::cout << "Median age = " << ComputeMedianAge(std::begin(persons), std::end(persons)) << std::endl;

	for (const auto& [message, pred] : functionsForComputing) {
		std::cout << message << ComputeMedianAge(std::begin(persons), std::partition(std::begin(persons), std::end(persons), pred)) << std::endl;
	}
}

int main() {
	using namespace std;

	vector<Person> persons = {
		{31, Gender::MALE, false},
		{40, Gender::FEMALE, true},
		{24, Gender::MALE, true},
		{20, Gender::FEMALE, true},
		{80, Gender::FEMALE, false},
		{78, Gender::MALE, false},
		{10, Gender::FEMALE, false},
		{55, Gender::MALE, true},
	};

	PrintStats(persons);

	return 0;
}
