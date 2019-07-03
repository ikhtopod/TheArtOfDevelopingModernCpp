#include <iostream>
#include <string>
#include <vector>

const std::string ADD = "ADD";
const std::string NEXT = "NEXT";
const std::string DUMP = "DUMP";

const std::vector<int> MONTHS {
	31, 28, 31, 30, 31, 30,
	31, 31, 30, 31, 30, 31,
};

int main() {
	int q = 0;
	std::cin >> q;

	int currentMonth = 0;
	int prevMonth = 0;

	std::vector<std::vector<std::string>> toDoList {};
	toDoList.resize(MONTHS[0] + 1, std::vector<std::string> {});

	for (int i = 0; i < q; ++i) {
		std::string operation {};
		std::cin >> operation;

		if (operation == NEXT) {
			prevMonth = currentMonth++;
			if (currentMonth > 11) currentMonth = 0;
			if (prevMonth == currentMonth) continue;

			for (int i = MONTHS[currentMonth] + 1; i <= MONTHS[prevMonth]; ++i) {
				toDoList[MONTHS[currentMonth]].insert(
					std::end(toDoList[MONTHS[currentMonth]]),
					std::begin(toDoList[i]),
					std::end(toDoList[i])
				);
			}//rof

			toDoList.resize(MONTHS[currentMonth] + 1, std::vector<std::string> {});
		} else {
			int num = 0;
			std::cin >> num;

			if (operation == DUMP) {
				std::cout << toDoList[num].size();

				for (const auto& str : toDoList[num]) {
					std::cout << " " << str;
				}//rof

				std::cout << std::endl;
			} else if (operation == ADD) {
				std::string tmp {};
				std::cin >> tmp;
				toDoList[num].push_back(tmp);
			}//fi
		}//fi
	}//rof

	return 0;
}
