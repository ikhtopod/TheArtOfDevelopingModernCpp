#pragma once

#include <iostream>
#include <string>
#include <map>

#include "date.h"
#include "event.h"

class Database {
private:
	std::map<Date, Events> m_db {};

public:
	void Add(Date date, std::string event);
	void Add(Date date, Event event);

	std::string Last(Date date);
	void Print(std::ostream& os);

	template<typename Pred>
	int RemoveIf(Pred pred);

	template<typename Pred>
	std::string FindIf(Pred pred);
};

Date ParseDate(std::istream& is);
