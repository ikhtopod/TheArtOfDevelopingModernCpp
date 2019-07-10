#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>
#include <memory>
#include <map>
#include <set>



class _Exception {
protected:
	std::string m_message {};

public:
	explicit _Exception() : _Exception("") {}
	explicit _Exception(std::string message)
		: m_message(message) {}

	virtual std::string what() const {
		return m_message;
	}
};

class DateException : public _Exception {
public:
	explicit DateException() : _Exception() {}
	explicit DateException(std::string message) :
		_Exception(message) {}
};

class OperationException : public _Exception {
public:
	explicit OperationException() : _Exception() {}
	explicit OperationException(std::string message) :
		_Exception(message) {}
};

class CommandHandlerException : public _Exception {
public:
	explicit CommandHandlerException() : _Exception() {}
	explicit CommandHandlerException(std::string message) :
		_Exception(message) {}
};


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
	static const int MIN_MONTH = 1;
	static const int MIN_DAY = 1;

	static const int MAX_MONTH = 12;
	static const int MAX_DAY = 31;

private:
	int m_day {};
	int m_month {};
	int m_year {};

private:
	void checkValidityDate() {
		if (m_month < Date::MIN_MONTH || m_month > Date::MAX_MONTH) {
			throw DateException("Month value is invalid: " + std::to_string(m_month));
		} else if (m_day < Date::MIN_DAY || m_day > Date::MAX_DAY) {
			throw DateException("Day value is invalid: " + std::to_string(m_day));
		}
	}

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

	void reset() {
		m_year = 0;
		m_month = 0;
		m_day = 0;
	}

	friend std::ostream& operator<<(std::ostream& lhs, const Date& rhs) {
		lhs << std::setfill('0') <<
			std::setw(4) << rhs.m_year << "-" <<
			std::setw(2) << rhs.m_month << "-" <<
			std::setw(2) << rhs.m_day;

		return lhs;
	}

	friend std::istream& operator>>(std::istream& lhs, Date& rhs) {
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

		if (operation.empty()) {
			return lhs;
		}

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
		if (cmd.empty()) {
			throw CommandHandlerException();
		}

		m_cmd = std::stringstream { cmd };
		m_cmd >> m_operation >> m_date >> m_event;

		return assign();
	}
};


int main() {
	Database db {};
	CommandHandler ch {};

	std::string command;
	while (std::getline(std::cin, command)) {
		try {
			ch.handle(command)->run(db);
		} catch (OperationException& e) {
			std::cout << e.what() << std::endl;
		} catch (DateException& e) {
			std::cout << e.what() << std::endl;
		} catch (CommandHandlerException&) {}
	}

	return 0;
}
