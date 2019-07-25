#pragma once

#include <iostream>
#include <string>
#include <functional>

#include "date.h"

class Database {
public:
	void Add(Date, std::string);
	std::string Last(Date);
	void Print(std::ostream& os);

	template<typename Pred>
	int RemoveIf(Pred pred);

	template<typename Pred>
	std::string FindIf(Pred pred);
};

Date ParseDate(std::istream& is);
