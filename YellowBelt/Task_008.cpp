#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
	NewBus,
	BusesForStop,
	StopsForBus,
	AllBuses
};

struct Query {
	QueryType type;
	string bus;
	string stop;
	vector<string> stops;
};

istream& operator>>(istream& is, Query& q) {
	if (string type {}; is >> type) {
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

struct BusesForStopResponse {
	const map<string, vector<string>>& stopsToBuses;
	const string& stop;
};

ostream& operator<<(ostream& os, const BusesForStopResponse& r) {
	if (r.stopsToBuses.count(r.stop) == 0) {
		os << "No stop";
	} else {
		for (const string& bus : r.stopsToBuses.at(r.stop)) {
			os << bus << " ";
		}//rof
	}//fi

	return os;
}

struct StopsForBusResponse {
	const map<string, vector<string>>& busesToStops;
	const map<string, vector<string>>& stopsToBuses;
	const string& bus;
};

ostream& operator<<(ostream& os, const StopsForBusResponse& r) {
	if (r.busesToStops.count(r.bus) == 0) {
		os << "No bus";
	} else {
		const size_t total = r.busesToStops.at(r.bus).size();
		size_t counter = 0;
		for (const string& stop : r.busesToStops.at(r.bus)) {
			os << "Stop " << stop << ": ";

			if (r.stopsToBuses.at(stop).size() == 1) {
				os << "no interchange";
			} else {
				for (const string& other_bus : r.stopsToBuses.at(stop)) {
					if (r.bus != other_bus) {
						os << other_bus << " ";
					}//fi
				}//rof
			}//fi

			if (++counter < total) {
				os << endl;
			}//fi
		}//rof
	}//fi

	return os;
}

struct AllBusesResponse {
	const map<string, vector<string>>& busesToStops;
};

ostream& operator<<(ostream& os, const AllBusesResponse& r) {
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
				os << endl;
			}//fi
		}//rof
	}//fi

	return os;
}

class BusManager {
private:
	map<string, vector<string>> m_busesToStops {};
	map<string, vector<string>> m_stopsToBuses {};

public:
	void AddBus(const string& bus, const vector<string>& stops) {
		m_busesToStops[bus] = stops;

		for (const auto& stop : stops) {
			m_stopsToBuses[stop].push_back(bus);
		}//rof
	}

	BusesForStopResponse GetBusesForStop(const string& stop) const {
		return BusesForStopResponse { m_stopsToBuses, stop };
	}

	StopsForBusResponse GetStopsForBus(const string& bus) const {
		return StopsForBusResponse { m_busesToStops, m_stopsToBuses, bus };
	}

	AllBusesResponse GetAllBuses() const {
		return AllBusesResponse { m_busesToStops };
	}
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
	int query_count;
	Query q;

	cin >> query_count;

	BusManager bm;
	for (int i = 0; i < query_count; ++i) {
		cin >> q;
		switch (q.type) {
			case QueryType::NewBus:
				bm.AddBus(q.bus, q.stops);
				break;
			case QueryType::BusesForStop:
				cout << bm.GetBusesForStop(q.stop) << endl;
				break;
			case QueryType::StopsForBus:
				cout << bm.GetStopsForBus(q.bus) << endl;
				break;
			case QueryType::AllBuses:
				cout << bm.GetAllBuses() << endl;
				break;
		}
	}

	return 0;
}
