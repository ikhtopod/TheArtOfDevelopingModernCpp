#include <iostream>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <map>
#include <set>

using namespace std;

class Rational {
private:
	int m_numerator = 0;
	int m_denominator = 1;

private:
	int getGcd() const {
		int a = std::abs(m_numerator);
		int b = std::abs(m_denominator);

		while (b != 0) {
			int tmp = a;
			a = b;
			b = tmp % b;
		}

		return a;
	}

	void reduceFraction() {
		for (int gcd = getGcd(); gcd != 1; gcd = getGcd()) {
			m_numerator /= gcd;
			m_denominator /= gcd;
		}
	}

	void normalize() {
		if (m_denominator == 0) {
			throw std::invalid_argument("Invalid argument");
		}

		if (m_numerator == 0) {
			m_denominator = 1;
		} else if (m_numerator < 0 && m_denominator < 0) {
			m_numerator = std::abs(m_numerator);
			m_denominator = std::abs(m_denominator);
		} else if (m_numerator < 0 || m_denominator < 0) {
			m_numerator = -std::abs(m_numerator);
			m_denominator = std::abs(m_denominator);
		}//fi

		reduceFraction();
	}

public:
	Rational() : Rational(0, 1) {}

	Rational(int numerator, int denominator) {
		m_numerator = numerator;
		m_denominator = denominator;

		normalize();
	}

	int Numerator() const {
		return m_numerator;
	}

	int Denominator() const {
		return m_denominator;
	}

public:
	bool operator==(const Rational& rhs) const {
		return m_numerator == rhs.m_numerator &&
			m_denominator == rhs.m_denominator;
	}

	bool operator<(const Rational& rhs) const {
		return (m_numerator * rhs.m_denominator) < (rhs.m_numerator * m_denominator);
	}

	Rational operator+(const Rational& rhs) const {
		int num = 0, den = 0;

		if (m_denominator == rhs.m_denominator) {
			num = m_numerator + rhs.m_numerator;
			den = m_denominator;
		} else {
			num = (m_numerator * rhs.m_denominator) + (rhs.m_numerator * m_denominator);
			den = m_denominator * rhs.m_denominator;
		}//fi

		return Rational { num, den };
	}

	Rational operator-(const Rational& rhs) const {
		int num = 0, den = 0;

		if (m_denominator == rhs.m_denominator) {
			num = m_numerator - rhs.m_numerator;
			den = m_denominator;
		} else {
			num = (m_numerator * rhs.m_denominator) - (rhs.m_numerator * m_denominator);
			den = m_denominator * rhs.m_denominator;
		}//fi

		return Rational { num, den };
	}

	Rational operator*(const Rational& rhs) const {
		return Rational { m_numerator * rhs.m_numerator, m_denominator * rhs.m_denominator };
	}

	Rational operator/(const Rational& rhs) const {
		if (m_denominator == 0 || rhs.m_numerator == 0) {
			throw std::domain_error("Division by zero");
		}

		return Rational { m_numerator * rhs.m_denominator, m_denominator * rhs.m_numerator };
	}

	friend ostream& operator<<(ostream& lhs, const Rational& rhs) {
		lhs << rhs.m_numerator << "/" << rhs.m_denominator;
		return lhs;
	}

	friend istream& operator>>(istream& lhs, Rational& rhs) {
		lhs >> rhs.m_numerator;
		lhs.ignore(1);
		lhs >> rhs.m_denominator;

		rhs.normalize();

		return lhs;
	}
};


const char ADD = '+';
const char SUB = '-';
const char MUL = '*';
const char DIV = '/';

int main() {
	Rational r1, r2;
	char operation = 0;

	try {
		std::cin >> r1 >> operation >> r2;

		if (operation == ADD) {
			std::cout << r1 + r2;
		} else if (operation == SUB) {
			std::cout << r1 - r2;
		} else if (operation == MUL) {
			std::cout << r1 * r2;
		} else if (operation == DIV) {
			std::cout << r1 / r2;
		}//fi
	} catch (const std::exception& ex) {
		std::cout << ex.what();
	}

	return 0;
}
