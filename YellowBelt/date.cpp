#include "date.h"

void Date::checkValidityDate() {
	if (m_month < Date::MIN_MONTH || m_month > Date::MAX_MONTH) {
		throw DateException("Month value is invalid: " + std::to_string(m_month));
	} else if (m_day < Date::MIN_DAY || m_day > Date::MAX_DAY) {
		throw DateException("Day value is invalid: " + std::to_string(m_day));
	}
}

int Date::GetAllDays() const {
	return m_day + (m_month * MAX_DAY) + (m_year * MAX_MONTH);
}

Date::Date() : Date(0, 0, 0) {}
Date::Date(int day, int month, int year) :
	m_day(day), m_month(month), m_year(year) {}

int Date::GetDay() const { return m_day; }
int Date::GetMonth() const { return m_month; }
int Date::GetYear() const { return m_year; }

bool Date::operator==(const Date& rhs) const {
	if (this == &rhs) return true;

	return (m_year == rhs.m_year) &&
		(m_month == rhs.m_month) &&
		(m_day == rhs.m_day);
}

bool Date::operator<(const Date& rhs) const {
	if (this == &rhs) return false;

	if (m_year != rhs.m_year) {
		return m_year < rhs.m_year;
	}

	if (m_month != rhs.m_month) {
		return m_month < rhs.m_month;
	}

	if (m_day != rhs.m_day) {
		return m_day < rhs.m_day;
	}

	return false;
}

bool Date::operator!=(const Date& rhs) const {
	return !(*this == rhs);
}

bool Date::operator<=(const Date& rhs) const {
	return !(rhs < *this);
}

bool Date::operator>(const Date& rhs) const {
	return rhs < *this;
}

bool Date::operator>=(const Date& rhs) const {
	return !(*this < rhs);
}

int Date::operator-(const Date& rhs) const {
	return GetAllDays() - rhs.GetAllDays();
}

void Date::reset() {
	m_year = 0;
	m_month = 0;
	m_day = 0;
}

std::ostream& operator<<(std::ostream& lhs, const Date& rhs) {
	lhs << std::setfill('0') <<
		std::setw(4) << rhs.m_year << "-" <<
		std::setw(2) << rhs.m_month << "-" <<
		std::setw(2) << rhs.m_day;

	return lhs;
}

std::istream& operator>>(std::istream& lhs, Date& rhs) {
	rhs.reset();
	std::string tmp {};

	lhs >> tmp;
	std::stringstream date {};
	date << tmp;

	if (date.str().empty()) {
		return lhs;
	}

	char c1, c2;
	if ((date >> rhs.m_year >> c1 >> rhs.m_month >> c2 >> rhs.m_day) &&
		(date.eof() && c1 == '-' && c2 == '-')) {
		rhs.checkValidityDate();
	} else {
		throw DateException("Wrong date format: " + date.str());
	}

	return lhs;
}
