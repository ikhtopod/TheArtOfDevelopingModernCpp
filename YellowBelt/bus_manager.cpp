#include "bus_manager.h"

void BusManager::AddBus(const std::string& bus, const std::vector<std::string>& stops) {
	m_busesToStops[bus] = stops;

	for (const auto& stop : stops) {
		m_stopsToBuses[stop].push_back(bus);
	}//rof
}

BusesForStopResponse BusManager::GetBusesForStop(const std::string& stop) const {
	return BusesForStopResponse { m_stopsToBuses, stop };
}

StopsForBusResponse BusManager::GetStopsForBus(const std::string& bus) const {
	return StopsForBusResponse { m_busesToStops, m_stopsToBuses, bus };
}

AllBusesResponse BusManager::GetAllBuses() const {
	return AllBusesResponse { m_busesToStops };
}
