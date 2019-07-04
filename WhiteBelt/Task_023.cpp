#include <iostream>
#include <string>
#include <vector>
#include <map>


int main() {
	int q = 0;
	std::cin >> q;

	std::map<std::vector<std::string>, int> busRoutes {};

	for (int i = 0; i < q; ++i) {
		int count {};
		std::cin >> count;

		std::vector<std::string> stops {};
		for (int j = 0; j < count; ++j) {
			std::string stop {};
			std::cin >> stop;
			stops.push_back(stop);
		}//rof

		if (busRoutes.find(stops) == std::cend(busRoutes)) {
			// маршрута нет, надо добавить
			int newBus = busRoutes.size() + 1;
			busRoutes[stops] = newBus;
			std::cout << "New bus " << newBus << std::endl;
		} else {
			std::cout << "Already exists for " << busRoutes[stops] << std::endl;
		}//fi
	}//rof

	return 0;
}
