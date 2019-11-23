#include <iostream>
#include <algorithm>
#include <numeric>
#include <map>
#include <tuple>

#include "airline_ticket.h"
#include "test_runner.h"

using namespace std;

#ifdef RU_LIFANOFF_UTEST_TEST_RUNNER_H
using namespace ru::lifanoff::utest;
#endif;

bool operator==(const Date& lhs, const Date& rhs) {
	return tie(lhs.year, lhs.month, lhs.day) == tie(rhs.year, rhs.month, rhs.day);
}

bool operator==(const Time& lhs, const Time& rhs) {
	return tie(lhs.hours, lhs.minutes) == tie(lhs.hours, lhs.minutes);
}

bool operator<(const Date& lhs, const Date& rhs) {
	return tie(lhs.year, lhs.month, lhs.day) < tie(rhs.year, rhs.month, rhs.day);
}

bool operator<(const Time& lhs, const Time& rhs) {
	return tie(lhs.hours, lhs.minutes) < tie(lhs.hours, lhs.minutes);
}

bool operator!=(const Date& lhs, const Date& rhs) {
	return !(lhs == rhs);
}

bool operator!=(const Time& lhs, const Time& rhs) {
	return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& lhs, const Date& rhs) {
	return lhs << rhs.year << '-' << rhs.month << '-' << rhs.day;
}

std::ostream& operator<<(std::ostream& lhs, const Time& rhs) {
	return lhs << rhs.hours << ':' << rhs.minutes;
}


std::istream& operator>>(std::istream& lhs, Date& rhs) {
	char c_ignore; // or lhs.ignore(1)
	return lhs >> rhs.year >> c_ignore >> rhs.month >> c_ignore >> rhs.day;
}

std::istream& operator>>(std::istream& lhs, Time& rhs) {
	char c_ignore; // or lhs.ignore(1)
	return lhs >> rhs.hours >> c_ignore >> rhs.minutes;
}


#define UPDATE_FIELD(ticket, field, values)	{		\
		auto it = values.find(#field);				\
		if (it != values.end()) {					\
			istringstream is(it->second);			\
			is >> ticket.field;						\
		}											\
	}


void TestUpdate() {
	AirlineTicket t;
	t.price = 0;

	const map<string, string> updates1 = {
	  {"departure_date", "2018-2-28"},
	  {"departure_time", "17:40"},
	};
	UPDATE_FIELD(t, departure_date, updates1);
	UPDATE_FIELD(t, departure_time, updates1);
	UPDATE_FIELD(t, price, updates1);

	ASSERT_EQUAL(t.departure_date, (Date { 2018, 2, 28 }));
	ASSERT_EQUAL(t.departure_time, (Time { 17, 40 }));
	ASSERT_EQUAL(t.price, 0);

	const map<string, string> updates2 = {
	  {"price", "12550"},
	  {"arrival_time", "20:33"},
	};
	UPDATE_FIELD(t, departure_date, updates2);
	UPDATE_FIELD(t, departure_time, updates2);
	UPDATE_FIELD(t, arrival_time, updates2);
	UPDATE_FIELD(t, price, updates2);

	// updates2 не содержит ключей "departure_date" и "departure_time", поэтому
	// значения этих полей не должны измениться
	ASSERT_EQUAL(t.departure_date, (Date { 2018, 2, 28 }));
	ASSERT_EQUAL(t.departure_time, (Time { 17, 40 }));
	ASSERT_EQUAL(t.price, 12550);
	ASSERT_EQUAL(t.arrival_time, (Time { 20, 33 }));
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestUpdate);
}
