#include <iostream>
#include <string>
#include <vector>

struct Name {
	std::string first {};
	std::string last {};
};

struct Date {
	int day = 0;
	int month = 0;
	int year = 0;
};

struct Student {
	Name name {};
	Date date {};
};

int main() {
	int n = 0;
	std::cin >> n;

	std::vector<Student> students(n);
	for (auto& s : students) {
		std::cin >> s.name.first >> s.name.last;
		std::cin >> s.date.day >> s.date.month >> s.date.year;
	}//rof

	int m = 0;
	std::cin >> m;

	for (int i = 0; i < m; ++i) {
		std::string cmd {};
		int num = 0;

		std::cin >> cmd >> num;
		num--;

		if (cmd == "name" && num >= 0 && num < n) {
			std::cout << students[num].name.first << " " <<
				students[num].name.last << std::endl;
		} else if (cmd == "date" && num >= 0 && num < n) {
			std::cout << students[num].date.day << "." <<
				students[num].date.month << "." <<
				students[num].date.year << std::endl;
		} else {
			std::cout << "bad request" << std::endl;
		}//fi
	}//rof

	return 0;
}
