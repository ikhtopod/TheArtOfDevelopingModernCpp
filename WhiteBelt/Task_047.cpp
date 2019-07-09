#include <iostream>
#include <exception>
#include <system_error>
#include <string>

std::string AskTimeServer() {
	/* ƒл€ тестировани€ повставл€йте сюда код, реализующий различное поведение этой функии: */

	// нормальный возврат строкового значени€
	return std::string { "12:33:21" };
	// return std::string { "15:17:25" };

	// выброс исключени€ system_error
	// throw std::system_error(std::error_code());
	// throw std::system_error(std::error_code(), "throw system error test");

	// выброс другого исключени€ с сообщением
	// throw std::exception("throw exception test");
	// throw std::domain_error("throw domain error test");
	// throw std::invalid_argument("throw invalid argument test");
}

class TimeServer {
private:
	std::string LastFetchedTime = "00:00:00";

public:
	std::string GetCurrentTime() {
		try {
			LastFetchedTime = AskTimeServer();
		} catch (std::system_error&) {
		} catch (...) {
			throw;
		}

		return LastFetchedTime;
	}
};


int main() {
	TimeServer ts;

	try {
		std::cout << ts.GetCurrentTime() << std::endl;
	} catch (std::exception& e) {
		std::cout << "Exception got: " << e.what() << std::endl;
	}

	return 0;
}
