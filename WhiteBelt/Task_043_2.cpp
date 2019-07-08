#include <iostream>
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
};

int main() {
	{
		Rational r1(4, 6);
		Rational r2(2, 3);
		bool equal = r1 == r2;
		if (!equal) {
			cout << "4/6 != 2/3" << endl;
			return 1;
		}
	}

	{
		Rational a(2, 3);
		Rational b(4, 3);
		Rational c = a + b;
		bool equal = c == Rational(2, 1);
		if (!equal) {
			cout << "2/3 + 4/3 != 2" << endl;
			return 2;
		}
	}

	{
		Rational a(5, 7);
		Rational b(2, 9);
		Rational c = a - b;
		bool equal = c == Rational(31, 63);
		if (!equal) {
			cout << "5/7 - 2/9 != 31/63" << endl;
			return 3;
		}
	}

	cout << "OK" << endl;
	return 0;
}
