#include <iostream>
#include <string>
#include <vector>

const std::string WORRY_COUNT = "WORRY_COUNT";
const std::string WORRY = "WORRY";
const std::string QUIET = "QUIET";
const std::string COME = "COME";

int main() {
	int q = 0;
	std::cin >> q;

	std::vector<bool> queue {};
	std::vector<int> result {};

	for (int i = 0; i < q; ++i) {
		std::string operation {};
		std::cin >> operation;

		if (operation == WORRY_COUNT) {
			int counter = 0;

			for (const bool& b : queue) {
				if (b) ++counter;
			}//rof

			result.push_back(counter);
		} else {
			int num = 0;
			std::cin >> num;

			if (operation == COME) {
				if (num > 0) {
					for (int i = num; i > 0; --i) {
						queue.push_back(false);
					}//rof
				} else if (num < 0) {
					for (int i = num; i < 0; ++i) {
						queue.pop_back();
					}//rof
				}//fi
			} else if (operation == WORRY) {
				queue[num] = true;
			} else if (operation == QUIET) {
				queue[num] = false;
			}//fi
		}//fi
	}//rof

	for (const int& r : result) {
		std::cout << r << std::endl;
	}//rof

	return 0;
}
