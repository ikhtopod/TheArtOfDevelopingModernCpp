#include "database.h"

Date ParseDate(std::istream& is) {
	Date date {};
	is >> date;
	return date;
}

Database::MapCIter Database::FindNearestDate(const Date& date) const {
	if (m_db.empty()) return std::cend(m_db);

	if (m_db.size() == 1) {
		auto sole = std::cbegin(m_db);

		if (sole->first > date) {
			return std::cend(m_db);
		} else {
			return sole;
		}
	}

	auto le = m_db.lower_bound(date);

	if (le == std::cbegin(m_db)) {
		if (le->first > date) {
			return std::cend(m_db);
		} else {
			return le;
		}
	}

	if (le == std::cend(m_db)) {
		auto prev_lower = std::prev(le);

		if (prev_lower->first > date) {
			return std::cend(m_db);
		} else {
			return prev_lower;
		}
	}

	if (le->first > date) {
		auto prev_lower = std::prev(le);

		if (prev_lower->first > date) {
			return std::cend(m_db);
		} else {
			return prev_lower;
		}
	} else {
		return le;
	}
}

void Database::Add(const Date& date, const Event& event) {
	m_db[date].Add(event);
}

std::string Database::Last(const Date& date) const {
	MapCIter nearestDateIt = FindNearestDate(date);

	if (nearestDateIt == std::cend(m_db)) {
		throw std::invalid_argument { "" };
	}

	std::vector<Event> entries = nearestDateIt->second.GetValue();

	if (entries.empty()) {
		throw std::invalid_argument { "" };
	}

	std::ostringstream sstr {};
	sstr << nearestDateIt->first << " " << entries.back().GetValue();

	return sstr.str();
}

void Database::Print(std::ostream& os) const {
	for (const auto& [date, events] : m_db) {
		for (const auto& event : events.GetValue()) {
			os << date << " " << event << std::endl;
		}//rof
	}//rof
}

std::vector<std::string> Database::FindIf(std::function<bool(Date, std::string)> pred) const {
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

int Database::RemoveIf(std::function<bool(Date, std::string)> pred) {
	int totalOfDeletedEvents = 0;

	std::vector<Date> datesForErase {};

	for (const auto& [date, events] : m_db) {
		for (const auto& event : events.GetValue()) {
			if (pred(date, event.GetValue())) {
				m_db.at(date).Del(event);
				totalOfDeletedEvents++;
			}
		}

		if (m_db.at(date).GetValue().empty()) {
			datesForErase.push_back(date);
		}
	}

	for (const Date& d : datesForErase) {
		m_db.erase(d);
	}

	return totalOfDeletedEvents;
}
