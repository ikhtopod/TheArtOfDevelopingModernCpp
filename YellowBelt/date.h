#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>

#include "bd_exception.h"

class Date {
private:
	static const int MIN_MONTH = 1;
	static const int MIN_DAY = 1;

	static const int MAX_MONTH = 12;
	static const int MAX_DAY = 31;

private:
	int m_day {};
	int m_month {};
	int m_year {};

private:
	void checkValidityDate();
	int GetAllDays() const;

public:
	Date();
	Date(int day, int month, int year);

	int GetDay() const;
	int GetMonth() const;
	int GetYear() const;

	bool operator==(const Date& rhs) const;
	bool operator<(const Date& rhs) const;
	// Based on operators equal and less.
	bool operator!=(const Date& rhs) const;
	bool operator<=(const Date& rhs) const;
	bool operator>(const Date& rhs) const;
	bool operator>=(const Date& rhs) const;
	
	int operator-(const Date& rhs) const;

	void reset();

	friend std::ostream& operator<<(std::ostream& lhs, const Date& rhs);
	friend std::istream& operator>>(std::istream& lhs, Date& rhs);
};
