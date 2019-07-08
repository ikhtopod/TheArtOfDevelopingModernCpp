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

int main(int argc, char** argv) {
	example_writefile();

	return 0;
}
