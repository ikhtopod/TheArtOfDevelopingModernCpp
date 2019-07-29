#include "database.h"

Date ParseDate(std::istream& is) {
	Date date {};
	is >> date;
	return date;
}

Database::MapCIter Database::FindNearestDate(const Date& date) {
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

void Database::Add(const Date& date, const std::string& event) {
	Add(date, Event { event });
}

void Database::Add(const Date& date, const Event& event) {
	m_db[date].Add(event);
}

std::string Database::Last(const Date& date) {
	MapCIter nearestDateIt = FindNearestDate(date);

	if (nearestDateIt == std::cend(m_db)) {
		throw std::invalid_argument { "" };
	}

	std::set<Event> entries = nearestDateIt->second.GetValue();

	if (entries.empty()) {
		throw std::invalid_argument { "" };
	}

	auto lastEventIt = std::crbegin(entries);
	std::ostringstream sstr {};
	sstr << nearestDateIt->first << " " << lastEventIt->GetValue();

	return sstr.str();
}

void Database::Print(std::ostream& os) {
	for (const auto& [date, events] : m_db) {
		for (const auto& event : events.GetValue()) {
			os << date << " " << event << std::endl;
		}//rof
	}//rof
}
