#include "database.h"

Date ParseDate(std::istream& is) {
	Date date {};
	is >> date;
	return date;
}

void Database::Add(const Date& date, const std::string& event) {
	Add(date, Event { event });
}

void Database::Add(const Date& date, const Event& event) {
	m_db[date].Add(event);
}

void Database::Print(std::ostream& os) {
	for (const auto& [date, events] : m_db) {
		for (const auto& event : events.GetValue()) {
			std::cout << date << " " << event << std::endl;
		}//rof
	}//rof
}
