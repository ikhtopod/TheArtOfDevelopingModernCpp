#include "responses.h"

std::ostream& operator<<(std::ostream& os, const BusesForStopResponse& r) {
	if (r.stopsToBuses.count(r.stop) == 0) {
		os << "No stop";
	} else {
		for (const std::string& bus : r.stopsToBuses.at(r.stop)) {
			os << bus << " ";
		}//rof
	}//fi

	return os;
}

std::ostream& operator<<(std::ostream& os, const StopsForBusResponse& r) {
	if (r.busesToStops.count(r.bus) == 0) {
		os << "No bus";
	} else {
		const size_t total = r.busesToStops.at(r.bus).size();
		size_t counter = 0;
		for (const std::string& stop : r.busesToStops.at(r.bus)) {
			os << "Stop " << stop << ": ";

			if (r.stopsToBuses.at(stop).size() == 1) {
				os << "no interchange";
			} else {
				for (const std::string& other_bus : r.stopsToBuses.at(stop)) {
					if (r.bus != other_bus) {
						os << other_bus << " ";
					}//fi
				}//rof
			}//fi

			if (++counter < total) {
				os << std::endl;
			}//fi
		}//rof
	}//fi

	return os;
}

std::ostream& operator<<(std::ostream& os, const AllBusesResponse& r) {
	if (r.busesToStops.empty()) {
		os << "No buses";
	} else {
		const size_t total = r.busesToStops.size();
		size_t counter = 0;
		for (const auto& [bus, stops] : r.busesToStops) {
			os << "Bus " << bus << ": ";

			for (const auto& stop : stops) {
				os << stop << " ";
			}//rof

			if (++counter < total) {
				os << std::endl;
			}//fi
		}//rof
	}//fi

	return os;
}
