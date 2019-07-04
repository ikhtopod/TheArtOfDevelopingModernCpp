#include <iostream>
#include <string>
#include <map>

const std::string DUMP = "DUMP";
const std::string ABOUT = "ABOUT";
const std::string RENAME = "RENAME";
const std::string CHANGE_CAPITAL = "CHANGE_CAPITAL";

int main() {
	int q = 0;
	std::cin >> q;

	std::map<std::string, std::string> dictOfCapitals {};

	for (int i = 0; i < q; ++i) {
		std::string operation {};
		std::cin >> operation;

		if (operation == DUMP) {
			if (dictOfCapitals.empty()) {
				std::cout << "There are no countries in the world" << std::endl;
			} else {
				for (const auto& item : dictOfCapitals) {
					std::cout << item.first << "/" << item.second << " ";
				}//rof
				std::cout << std::endl;
			}//fi
		} else {
			std::string arg1 {};
			std::cin >> arg1;

			if (operation == ABOUT) {
				std::cout << "Country " << arg1;

				if (dictOfCapitals.find(arg1) == dictOfCapitals.cend()) {
					std::cout << " doesn't exist" << std::endl;
				} else {
					std::cout << " has capital " << dictOfCapitals[arg1] << std::endl;
				}//fi
			} else {
				std::string arg2 {};
				std::cin >> arg2;

				if (operation == RENAME) {
					if (arg1 == arg2 ||
						dictOfCapitals.find(arg1) == dictOfCapitals.cend() ||
						dictOfCapitals.find(arg2) != dictOfCapitals.cend()) {

						std::cout << "Incorrect rename, skip" << std::endl;
					} else {
						dictOfCapitals[arg2] = dictOfCapitals[arg1];
						dictOfCapitals.erase(arg1);

						std::cout << "Country " << arg1 <<
							" with capital " << dictOfCapitals[arg2] <<
							" has been renamed to " << arg2 << std::endl;
					}//fi
				} else if (operation == CHANGE_CAPITAL) {
					if (dictOfCapitals.find(arg1) == dictOfCapitals.cend()) {
						dictOfCapitals[arg1] = arg2;

						std::cout << "Introduce new country " << arg1 <<
							" with capital " << arg2 << std::endl;
					} else if (dictOfCapitals[arg1] == arg2) {
						std::cout << "Country " << arg1 <<
							" hasn't changed its capital" << std::endl;
					} else {
						std::cout << "Country " << arg1 <<
							" has changed its capital from " << dictOfCapitals[arg1] <<
							" to " << arg2 << std::endl;

						dictOfCapitals[arg1] = arg2;
					}//fi
				}//fi
			}//fi
		}//fi
	}//rof

	return 0;
}
