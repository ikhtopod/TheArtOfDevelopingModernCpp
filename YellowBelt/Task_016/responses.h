#pragma once

#ifndef RESPONSES_H
#define RESPONSES_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

struct BusesForStopResponse {
	const std::map<std::string, std::vector<std::string>>& stopsToBuses;
	const std::string& stop;
};

struct StopsForBusResponse {
	const std::map<std::string, std::vector<std::string>>& busesToStops;
	const std::map<std::string, std::vector<std::string>>& stopsToBuses;
	const std::string& bus;
};

struct AllBusesResponse {
	const std::map<std::string, std::vector<std::string>>& busesToStops;
};

std::ostream& operator<<(std::ostream& os, const BusesForStopResponse& r);
std::ostream& operator<<(std::ostream& os, const StopsForBusResponse& r);
std::ostream& operator<<(std::ostream& os, const AllBusesResponse& r);

#endif // !RESPONSES_H
