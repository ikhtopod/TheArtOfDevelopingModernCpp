#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#define DPRINT(ARG) std::cout << #ARG << " = " << ARG << std::endl;

struct Date {
	int day {};
	int month {};
	int year {};

	operator std::string() {
		return std::to_string(day) + "/" +
			std::to_string(month) + "/" +
			std::to_string(year);
	}
};

void example_readfile(std::string filename = "hello.txt") {
	std::ifstream file { filename };

	Date date {};
	if (file.is_open()) {
		for (auto* p : { &date.day, &date.month, &date.year }) {
			file >> *p;
			file.ignore(1);
		}
	} else {
		std::cout << "Warning: can't open file " << filename << " to read." << std::endl;
	}
	file.close();

	std::cout << "date: " << std::string { date } << std::endl;
}

void example_writefile(std::string filename = "hello_out.txt") {
	std::ofstream outfile { filename, std::ios::app };
	if (outfile.is_open()) {
		outfile << "09-10-2652";
	} else {
		std::cout << "Warning: can't open file " << filename << " to read." << std::endl;
	}
	outfile.close();

	example_readfile(filename);
}

void example_string_view(std::string_view sv) {
	std::cout << sv << std::endl;
}

void test_example_string_view() {
	example_string_view("test 0");

	const char* test1 = "test 1";
	example_string_view(test1);

	std::string test2 { "test 2" };
	example_string_view(test2);

	const std::string test3 { "test 3" };
	example_string_view(test3);

	std::string test4 { "test 4" };
	example_string_view(test4.c_str());

	const std::string test5 { "test 5" };
	example_string_view(test5.c_str());
}

int main(int argc, char** argv) {
	test_example_string_view();

	return 0;
}
