#pragma once

#ifndef BUS_MANAGER_H
#define BUS_MANAGER_H

#include <string>
#include <vector>
#include <map>

#include "responses.h"

class BusManager {
private:
	std::map<std::string, std::vector<std::string>> m_busesToStops {};
	std::map<std::string, std::vector<std::string>> m_stopsToBuses {};

public:
	void AddBus(const std::string& bus, const std::vector<std::string>& stops);
	BusesForStopResponse GetBusesForStop(const std::string& stop) const;
	StopsForBusResponse GetStopsForBus(const std::string& bus) const;
	AllBusesResponse GetAllBuses() const;
};

#endif // !BUS_MANAGER_H
