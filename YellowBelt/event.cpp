#include "event.h"

/* Event */

Event::Event() : Event("") {}
Event::Event(std::string event) : m_event(event) {}

bool Event::operator<(const Event& rhs) const { return m_event < rhs.m_event; }
bool Event::operator==(const Event& rhs) const { return m_event == rhs.m_event; }

std::ostream& operator<<(std::ostream& lhs, const Event& rhs) {
	lhs << rhs.m_event;
	return lhs;
}

std::istream& operator>>(std::istream& lhs, Event& rhs) {
	rhs.m_event = "";
	lhs >> rhs.m_event;

	return lhs;
}

bool Event::isEmpty() const { return m_event.empty(); }


/* Events */

Events::~Events() { m_events.clear(); }

std::set<Event> Events::GetValue() const { return m_events; }

void Events::Add(const Event& event) {
	m_events.insert(event);
}

bool Events::Del(const Event& event) {
	return static_cast<bool>(m_events.erase(event));
}
