#include "query.h"

std::istream& operator>>(std::istream& is, Query& q) {
	if (std::string type {}; is >> type) {
		if (type == "ALL_BUSES") {
			q.type = QueryType::AllBuses;
		} else if (type == "STOPS_FOR_BUS") {
			q.type = QueryType::StopsForBus;
			is >> q.bus;
		} else if (type == "BUSES_FOR_STOP") {
			q.type = QueryType::BusesForStop;
			is >> q.stop;
		} else if (type == "NEW_BUS") {
			q.type = QueryType::NewBus;

			if (size_t count {}; is >> q.bus >> count) {
				q.stops.resize(count);

				for (auto& stop : q.stops) {
					is >> stop;
				}//rof
			}//fi
		}//fi
	}//fi

	return is;
}
