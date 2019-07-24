#include <iostream>
#include <string>


void SendSms(const std::string& number, const std::string& message) {
	std::cout << "Send '" << message << "' to number " << number << std::endl;
}

void SendEmail(const std::string& email, const std::string& message) {
	std::cout << "Send '" << message << "' to e-mail " << email << std::endl;
}

class INotifier {
public:
	virtual void Notify(const std::string& message) = 0;
};

class SmsNotifier : public INotifier {
private:
	std::string m_number;

public:
	SmsNotifier(const std::string& number) : m_number(number) {}

	virtual void Notify(const std::string& message) override {
		SendSms(m_number, message);
	}
};

class EmailNotifier : public INotifier {
private:
	std::string m_email;

public:
	EmailNotifier(const std::string& email) : m_email(email) {}

	virtual void Notify(const std::string& message) override {
		SendEmail(m_email, message);
	}
};

void Notify(INotifier& notifier, const std::string& message) {
	notifier.Notify(message);
}

using namespace std;

int main() {
	SmsNotifier sms { "+7-495-777-77-77" };
	EmailNotifier email { "na-derevnyu@dedushke.ru" };

	Notify(sms, "I have White belt in C++");
	Notify(email, "And want a Yellow one");
	return 0;
}
