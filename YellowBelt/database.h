#pragma once

#include <stdexcept>
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

#include "date.h"
#include "event.h"

class Database {
private:
	std::map<Date, Events> m_db {};

protected:
	using MapCIter = std::map<Date, Events>::const_iterator;

	MapCIter FindNearestDate(const Date& date) const;

public:
	void Add(const Date& date, const Event& event);

	std::string Last(const Date& date) const;
	void Print(std::ostream& os) const;

	std::vector<std::string> FindIf(std::function<bool(Date, std::string)> pred) const;

	int RemoveIf(std::function<bool(Date, std::string)> pred);
};

Date ParseDate(std::istream& is);
