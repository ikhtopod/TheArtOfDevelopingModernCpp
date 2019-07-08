#include <iostream>
#include <sstream>
#include <cmath>
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
	Rational() {
		m_numerator = 0;
		m_denominator = 1;
	}

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

int main() {
	{
		ostringstream output;
		output << Rational(-6, 8);
		if (output.str() != "-3/4") {
			cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
			return 1;
		}
	}

	{
		istringstream input("5/7");
		Rational r;
		input >> r;
		bool equal = r == Rational(5, 7);
		if (!equal) {
			cout << "5/7 is incorrectly read as " << r << endl;
			return 2;
		}
	}

	{
		istringstream input("5/7 10/8");
		Rational r1, r2;
		input >> r1 >> r2;
		bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
		if (!correct) {
			cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
			return 3;
		}

		input >> r1;
		input >> r2;
		correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
		if (!correct) {
			cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
			return 4;
		}
	}

	cout << "OK" << endl;
	return 0;
}
