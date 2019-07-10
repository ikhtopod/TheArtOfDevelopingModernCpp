#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <memory>
#include <map>
#include <set>


class Event {
private:
	std::string m_event {};

public:
	explicit Event() : Event("") {}
	explicit Event(std::string event) : m_event(event) {}

	bool operator<(const Event& rhs) const { return m_event < rhs.m_event; }
	bool operator==(const Event& rhs) const { return m_event == rhs.m_event; }

	friend std::ostream& operator<<(std::ostream& lhs, const Event& rhs) {
		lhs << rhs.m_event;
		return lhs;
	}

	friend std::istream& operator>>(std::istream& lhs, Event& rhs) {
		rhs.m_event = "";
		lhs >> rhs.m_event;

		return lhs;
	}

	bool isEmpty() const { return m_event.empty(); }
};

class Events {
private:
	std::set<Event> m_events {};

public:
	explicit Events() = default;
	~Events() { m_events.clear(); }

	std::set<Event> GetValue() const { return m_events; }

	void Add(const Event& event) {
		m_events.insert(event);
	}

	bool Del(const Event& event) {
		return static_cast<bool>(m_events.erase(event));
	}

};

class Date {
private:
	int m_day {};
	int m_month {};
	int m_year {};

public:
	explicit Date() : Date(0, 0, 0) {}
	explicit Date(int day, int month, int year) :
		m_day(day), m_month(month), m_year(year) {}

	int GetDay() const { return m_day; }
	int GetMonth() const { return m_month; }
	int GetYear() const { return m_year; }

	bool operator<(const Date& rhs) const {
		if (m_year < rhs.m_year) {
			return true;
		} else if (m_year > rhs.m_year) {
			return false;
		}//fi year

		if (m_month < rhs.m_month) {
			return true;
		} else if (m_month > rhs.m_month) {
			return false;
		}//fi month

		if (m_day < rhs.m_day) {
			return true;
		} else if (m_day > rhs.m_day) {
			return false;
		}//fi day

		return false;
	}

	friend std::ostream& operator<<(std::ostream& lhs, const Date& rhs) {
		lhs << std::setfill('0') <<
			std::setw(4) << rhs.m_year << "-" <<
			std::setw(2) << rhs.m_month << "-" <<
			std::setw(2) << rhs.m_day;

		return lhs;
	}

	friend std::istream& operator>>(std::istream& lhs, Date& rhs) {
		int year = 0, month = 0, day = 0;

		lhs >> year;
		lhs.ignore(1);
		lhs >> month;
		lhs.ignore(1);
		lhs >> day;

		rhs.m_year = year;
		rhs.m_month = month;
		rhs.m_day = day;

		return lhs;
	}
};

class Database {
private:
	std::map<Date, Events> m_db {};

public:
	void AddEvent(const Date& date, const std::string& event) {
		AddEvent(date, Event { event });
	}

	void AddEvent(const Date& date, const Event& event) {
		m_db[date].Add(event);
	}

	bool DeleteEvent(const Date& date, const std::string& event) {
		DeleteEvent(date, Event { event });
	}

	bool DeleteEvent(const Date& date, const Event& event) {
		bool result = false;

		try {
			result = m_db.at(date).Del(event);
		} catch (std::out_of_range&) {
		} catch (...) {}

		return result;
	}

	int DeleteDate(const Date& date) {
		int totalOfDeletedEvents = 0;

		try {
			totalOfDeletedEvents = m_db.at(date).GetValue().size();
			m_db.erase(date);
		} catch (std::out_of_range&) {
		} catch (...) {}

		return totalOfDeletedEvents;
	}

	void Find(const Date& date) const {
		try {
			for (const auto& event : m_db.at(date).GetValue()) {
				std::cout << event << std::endl;
			}
		} catch (std::out_of_range&) {
		} catch (...) {}
	}

	void Print() const {
		for (const auto& [date, events] : m_db) {
			for (const auto& event : events.GetValue()) {
				std::cout << date << " " << event << std::endl;
			}//rof
		}//rof
	}
};


class ICommand {
public:
	virtual void run(Database& db) = 0;
};

class CommandAdd : public ICommand {
private:
	Date m_date;
	Event m_event;

public:
	CommandAdd(Date date, Event event) :
		m_date(date), m_event(event) {}

	virtual void run(Database& db) override {
		if (m_event.isEmpty()) return;

		db.AddEvent(m_date, m_event);
	}
};

class CommandFind : public ICommand {
private:
	Date m_date;

public:
	CommandFind(Date date) : m_date(date) {}

	virtual void run(Database& db) override {
		db.Find(m_date);
	}
};

class CommandPrint : public ICommand {
public:
	virtual void run(Database& db) override {
		db.Print();
	}
};

class CommandDel : public ICommand {};

class CommandDelDate : public CommandDel {
private:
	Date m_date;

public:
	CommandDelDate(Date date) : m_date(date) {}

	virtual void run(Database& db) override {
		int totalDeleted = db.DeleteDate(m_date);
		std::cout << "Deleted " << totalDeleted << " events" << std::endl;
	}
};

class CommandDelEvent : public CommandDel {
private:
	Date m_date;
	Event m_event;

public:
	CommandDelEvent(Date date, Event event) :
		m_date(date), m_event(event) {}

	virtual void run(Database& db) override {
		if (db.DeleteEvent(m_date, m_event)) {
			std::cout << "Deleted successfully" << std::endl;
		} else {
			std::cout << "Event not found" << std::endl;
		}//fi
	}
};


class OperationException : public std::exception {
public:
	explicit OperationException() : OperationException("") {}
	explicit OperationException(std::string message) :
		OperationException(message.c_str()) {}
	explicit OperationException(const char* const message) :
		std::exception(message) {}
};

enum class OperationType : uint8_t {
	NONE,
	ADD, DEL,
	FIND, PRINT
};

class Operation final {
private:
	inline static const std::string ADD { "Add" };
	inline static const std::string DEL { "Del" };
	inline static const std::string FIND { "Find" };
	inline static const std::string PRINT { "Print" };

private:
	OperationType m_operation {};

private:
	void init(const std::string& operation) {
		if (operation == ADD) {
			m_operation = OperationType::ADD;
		} else if (operation == DEL) {
			m_operation = OperationType::DEL;
		} else if (operation == FIND) {
			m_operation = OperationType::FIND;
		} else if (operation == PRINT) {
			m_operation = OperationType::PRINT;
		} else {
			m_operation = OperationType::NONE;
		}
	}

public:
	explicit Operation() : Operation("") {}
	explicit Operation(std::string operation) {
		init(operation);
	}

	friend std::istream& operator>>(std::istream& lhs, Operation& rhs) {
		std::string operation {};
		lhs >> operation;

		rhs.init(operation);

		if (rhs.isNone()) {
			throw OperationException("Unknown command: " + operation);
		}

		return lhs;
	}

	operator OperationType() const {
		return m_operation;
	}

	bool isNone() { return m_operation == OperationType::NONE; }
};


class CommandHandlerException : public std::exception {
public:
	explicit CommandHandlerException() : CommandHandlerException("") {}
	explicit CommandHandlerException(std::string message) :
		CommandHandlerException(message.c_str()) {}
	explicit CommandHandlerException(const char* const message) :
		std::exception(message) {}
};

class CommandHandler final {
private:
	std::stringstream m_cmd {};

	Operation m_operation {};
	Date m_date {};
	Event m_event {};

private:
	std::shared_ptr<ICommand> assign() const {
		std::shared_ptr<ICommand> p_cmd { nullptr };

		switch (m_operation) {
			case OperationType::ADD:
				p_cmd = std::make_shared<CommandAdd>(m_date, m_event);
				break;
			case OperationType::DEL:
			{
				if (m_event.isEmpty()) {
					p_cmd = std::make_shared<CommandDelDate>(m_date);
				} else {
					p_cmd = std::make_shared<CommandDelEvent>(m_date, m_event);
				}//fi

				break;
			}
			case OperationType::FIND:
				p_cmd = std::make_shared<CommandFind>(m_date);
				break;
			case OperationType::PRINT:
				p_cmd = std::make_shared<CommandPrint>();
				break;
		}

		return p_cmd;
	}

public:
	std::shared_ptr<ICommand> handle(const std::string& cmd) {
		m_cmd = std::stringstream { cmd };

		m_cmd >> m_operation >> m_date >> m_event;

		if (m_operation.isNone()) {
			throw CommandHandlerException();
		}

		return assign();
	}
};


int main() {
	Database db {};
	CommandHandler ch {};

	std::string command;
	while (std::getline(std::cin, command)) {
		if (command.empty()) continue;

		try {
			ch.handle(command)->run(db);
		} catch (OperationException& e) {
			std::cout << e.what() << std::endl;
		} catch (...) {}
	}

	return 0;
}
