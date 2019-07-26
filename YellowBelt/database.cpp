#include "database.h"

Date ParseDate(std::istream& is) {
	Date date {};
	is >> date;
	return date;
}

void Database::Add(Date date, std::string event) {
	Add(date, Event { event });
}
