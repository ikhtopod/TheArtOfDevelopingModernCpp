#include "database.h"

Date ParseDate(std::istream& is) {
	Date date {};
	is >> date;
	return date;
}

Database::MapCIter Database::FindNearestDate(const Date& date) {
	if (m_db.empty()) return std::cend(m_db);

	auto lower = m_db.lower_bound(date);

	if (lower == std::cend(m_db)) {
		return std::prev(std::cend(m_db));
	} else if (lower == std::cbegin(m_db)) {
		if (lower->first == date) {
			return lower;
		} else {
			return std::cend(m_db);
		}
	}

	auto prev_lower = std::prev(lower);

	int left_dist = date - prev_lower->first;
	int right_dist = lower->first - date;

	return left_dist <= right_dist ? prev_lower : lower;
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

	return std::crbegin(entries)->GetValue();
}

void Database::Print(std::ostream& os) {
	for (const auto& [date, events] : m_db) {
		for (const auto& event : events.GetValue()) {
			std::cout << date << " " << event << std::endl;
		}//rof
	}//rof
}
