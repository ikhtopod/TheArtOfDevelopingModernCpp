#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>

class Event {
private:
	std::string m_event {};

public:
	Event();
	Event(const char* event);
	Event(const std::string& event);

	bool operator==(const Event& rhs) const;
	bool operator<(const Event& rhs) const;
	// Based on operators equal and less.
	bool operator!=(const Event& rhs) const;
	bool operator<=(const Event& rhs) const;
	bool operator>(const Event& rhs) const;
	bool operator>=(const Event& rhs) const;

	friend std::ostream& operator<<(std::ostream& lhs, const Event& rhs);
	friend std::istream& operator>>(std::istream& lhs, Event& rhs);

	std::string GetValue() const;
	bool IsEmpty() const;
};

class Events {
private:
	std::set<Event> m_uniqueEvents {};
	std::vector<Event> m_events {};

public:
	explicit Events() = default;
	~Events();

	std::vector<Event> GetValue() const;

	void Add(const Event& event);
	void Del(const Event& event);
};
