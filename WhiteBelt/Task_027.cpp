#include <iostream>
#include <string>
#include <map>
#include <set>


int main() {
	int q = 0;
	std::cin >> q;

	std::map<std::set<std::string>, int> busRoutes {};

	for (int i = 0; i < q; ++i) {
		int count {};
		std::cin >> count;

		std::set<std::string> stops {};
		for (int j = 0; j < count; ++j) {
			std::string stop {};
			std::cin >> stop;
			stops.insert(stop);
		}//rof

		if (busRoutes.find(stops) == std::cend(busRoutes)) {
			int newBus = busRoutes.size() + 1;
			busRoutes[stops] = newBus;
			std::cout << "New bus " << newBus << std::endl;
		} else {
			std::cout << "Already exists for " << busRoutes[stops] << std::endl;
		}//fi
	}//rof

	return 0;
}
