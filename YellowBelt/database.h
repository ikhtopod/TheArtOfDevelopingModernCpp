#pragma once

#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <set>

#include "date.h"
#include "event.h"

class Database {
private:
	std::map<Date, Events> m_db {};

protected:
	using MapCIter = std::map<Date, Events>::const_iterator;
	MapCIter FindNearestDate(const Date& date);

public:
	void Add(const Date& date, const std::string& event);
	void Add(const Date& date, const Event& event);

	std::string Last(const Date& date);
	void Print(std::ostream& os);

	template<typename Pred>
	std::vector<std::string> FindIf(Pred& pred) {
		std::vector<std::string> entries {};
		std::ostringstream ostr {};

		for (const auto& [date, events] : m_db) {
			for (const auto& event : events.GetValue()) {
				if (pred(date, event.GetValue())) {
					ostr.str("");
					ostr << date << " " << event.GetValue();
					entries.push_back(ostr.str());
				}
			}
		}

		return entries;
	}

	template<typename Pred>
	int RemoveIf(Pred& pred) {
		int totalOfDeletedEvents = 0;

		for (const auto& [date, events] : m_db) {
			for (const auto& event : events.GetValue()) {
				if (pred(date, event.GetValue())) {
					m_db.at(date).Del(event);
					totalOfDeletedEvents++;
				}
			}
		}

		return totalOfDeletedEvents;
	}
};

Date ParseDate(std::istream& is);
