#include "phone_number.h"

// task 14

#include <sstream>
#include <stdexcept>

PhoneNumber::PhoneNumber(const std::string& international_number) {
	std::istringstream tmp { international_number };

	std::string str_plus {};
	std::getline(tmp, str_plus, '+');
	std::getline(tmp, country_code_, '-');
	std::getline(tmp, city_code_, '-');
	std::getline(tmp, local_number_);

	if (!str_plus.empty() ||
		country_code_.empty() || city_code_.empty() || local_number_.empty()) {
		throw std::invalid_argument { "" };
	}
}

std::string PhoneNumber::GetCountryCode() const {
	return country_code_;
}

std::string PhoneNumber::GetCityCode() const {
	return city_code_;
}

std::string PhoneNumber::GetLocalNumber() const {
	return local_number_;
}

std::string PhoneNumber::GetInternationalNumber() const {
	std::stringstream international_number {};

	international_number << '+' << GetCountryCode() << '-'
		<< GetCityCode() << '-'
		<< GetLocalNumber();

	return international_number.str();
}


#include <iostream>

int main() {
	{
		std::string number = "+7-495-111-22-33";
		try {
			PhoneNumber pn { number };
			std::cout << number << " = " << pn.GetInternationalNumber() << std::endl;
		} catch (const std::invalid_argument&) {
			std::cout << number << " not correct" << std::endl;
		}
	}

	{
		std::string number = "+7-495-1112233";
		try {
			PhoneNumber pn { number };
			std::cout << number << " = " << pn.GetInternationalNumber() << std::endl;
		} catch (const std::invalid_argument&) {
			std::cout << number << " not correct" << std::endl;
		}
	}

	{
		std::string number = "+323-22-460002";
		try {
			PhoneNumber pn { number };
			std::cout << number << " = " << pn.GetInternationalNumber() << std::endl;
		} catch (const std::invalid_argument&) {
			std::cout << number << " not correct" << std::endl;
		}
	}

	{
		std::string number = "+1-2-coursera-cpp";
		try {
			PhoneNumber pn { number };
			std::cout << number << " = " << pn.GetInternationalNumber() << std::endl;
		} catch (const std::invalid_argument&) {
			std::cout << number << " not correct" << std::endl;
		}
	}

	{
		std::string number = "1-2-333";
		try {
			PhoneNumber pn { number };
			std::cout << number << " = " << pn.GetInternationalNumber() << std::endl;
		} catch (const std::invalid_argument&) {
			std::cout << number << " not correct" << std::endl;
		}
	}

	{
		std::string number = "+7-1233";
		try {
			PhoneNumber pn { number };
			std::cout << number << " = " << pn.GetInternationalNumber() << std::endl;
		} catch (const std::invalid_argument&) {
			std::cout << number << " not correct" << std::endl;
		}
	}

	return 0;
}
