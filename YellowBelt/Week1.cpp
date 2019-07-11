#include <iostream>
#include <string>

#define DPRINT(ARG) std::cout << "[" << #ARG << "]\t" << ARG << std::endl

class IException {
public:
	virtual std::string what() const = 0;
};

class BaseException : public IException {
private:
	std::string m_message {};

public:
	explicit BaseException() : BaseException(std::string {}) {}
	explicit BaseException(std::string message) : m_message(message) {}
	virtual ~BaseException() = default;

	virtual std::string what() const override { return m_message; }
};

class WrongException : public BaseException {
public:
	explicit WrongException() : BaseException() {}
	explicit WrongException(std::string message) : BaseException(message) {}
	virtual ~WrongException() = default;
};

class BigTroubleException : public BaseException {
public:
	explicit BigTroubleException() : BaseException() {}
	explicit BigTroubleException(std::string message) : BaseException(message) {}
	virtual ~BigTroubleException() = default;
};

class NonexistentParameterException : public BaseException {
public:
	explicit NonexistentParameterException() : BaseException() {}
	explicit NonexistentParameterException(std::string message) : BaseException(message) {}
	virtual ~NonexistentParameterException() = default;
};

int main() {
	DPRINT("BEGIN LOOP");

	uint8_t exceptionFlag = 0;
	try {
		while (true) {
			try {
				switch (exceptionFlag++) {
					case 0:
						throw BaseException("BaseException");
					case 1:
						throw WrongException("WrongException");
					case 2:
						throw BigTroubleException("BigTroubleException");
					case 3:
						throw NonexistentParameterException("NonexistentParameterException");
					default:
						throw "";
				}
			} catch (IException& e) {
				DPRINT(e.what());
			}
		}
	} catch (...) {
		DPRINT("END LOOP");
	}

	return 0;
}
