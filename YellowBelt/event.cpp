#include "event.h"

/* Event */

Event::Event() : Event("") {}
Event::Event(const char* event) : Event(std::string { event }) {}
Event::Event(const std::string& event) : m_event(event) {}

bool Event::operator==(const Event& rhs) const {
	if (this == &rhs) return true;

	return m_event == rhs.m_event;
}

bool Event::operator<(const Event& rhs) const {
	if (this == &rhs) return false;

	return m_event < rhs.m_event;
}

bool Event::operator!=(const Event& rhs) const {
	return !(*this == rhs);
}

bool Event::operator<=(const Event& rhs) const {
	return !(rhs < *this);
}

bool Event::operator>(const Event& rhs) const {
	return rhs < *this;
}

bool Event::operator>=(const Event& rhs) const {
	return !(*this < rhs);
}

std::ostream& operator<<(std::ostream& lhs, const Event& rhs) {
	return lhs << rhs.m_event;
}

std::istream& operator>>(std::istream& lhs, Event& rhs) {
	rhs.m_event = "";
	lhs >> std::ws;
	return std::getline(lhs, rhs.m_event);
}

std::string Event::GetValue() const {
	return m_event;
}

bool Event::IsEmpty() const { return m_event.empty(); }


/* Events */

Events::~Events() {
	m_uniqueEvents.clear();
	m_events.clear();
}

std::vector<Event> Events::GetValue() const {
	return m_events;
}

void Events::Add(const Event& event) {
	if (m_uniqueEvents.count(event) != 0) {
		return;
	}

	m_uniqueEvents.insert(event);
	m_events.push_back(event);
}

void Events::Del(const Event& event) {
	if (m_uniqueEvents.erase(event) != 0) {
		m_events.erase(std::find(std::begin(m_events), std::end(m_events), event));
	}
}
