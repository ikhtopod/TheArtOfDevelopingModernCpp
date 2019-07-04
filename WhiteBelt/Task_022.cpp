#include <iostream>
#include <string>
#include <vector>
#include <map>

const std::string ALL_BUSES = "ALL_BUSES";
const std::string STOPS_FOR_BUS = "STOPS_FOR_BUS";
const std::string BUSES_FOR_STOP = "BUSES_FOR_STOP";
const std::string NEW_BUS = "NEW_BUS";

int main() {
	int q = 0;
	std::cin >> q;

	std::map<std::string, std::vector<std::string>> listStops {};
	std::map<std::string, std::vector<std::string>> busStops {};

	for (int i = 0; i < q; ++i) {
		std::string operation {};
		std::cin >> operation;

		if (operation == ALL_BUSES) {
			if (busStops.empty()) {
				std::cout << "No buses" << std::endl;
			} else {
				for (const auto& bus : busStops) {
					std::cout << "Bus " << bus.first << ":";

					for (const auto& stop : bus.second) {
						std::cout << " " << stop;
					}//rof

					std::cout << std::endl;
				}//rof
			}//fi
		} else {
			std::string arg1 {};
			std::cin >> arg1;

			if (operation == STOPS_FOR_BUS) {
				if (busStops.find(arg1) == std::cend(busStops)) {
					std::cout << "No bus" << std::endl;
				} else {
					for (const auto& stop : busStops[arg1]) {
						std::cout << "Stop " << stop << ":";

						if (listStops[stop].size() < 2) {
							std::cout << " no interchange";
						} else {
							for (const auto& bus : listStops[stop]) {
								if (bus == arg1) continue;
								std::cout << " " << bus;
							}//rof
						}//fi

						std::cout << std::endl;
					}//rof
				}//fi
			} else if (operation == BUSES_FOR_STOP) {
				if (listStops.find(arg1) == std::cend(listStops)) {
					std::cout << "No stop" << std::endl;
				} else {
					for (const auto& bus : listStops[arg1]) {
						std::cout << bus << " ";
					}//rof

					std::cout << std::endl;
				}//fi
			} else {
				int arg2 {};
				std::cin >> arg2;

				if (operation == NEW_BUS) {
					for (int j = 0; j < arg2; ++j) {
						std::string stop {};
						std::cin >> stop;
						busStops[arg1].push_back(stop);
						listStops[stop].push_back(arg1);
					}//rof
				}//fi
			}//fi
		}//fi
	}//rof

	return 0;
}
