#include <iostream>
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
		const set<Rational> rs = { {1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2} };
		if (rs.size() != 3) {
			cout << "Wrong amount of items in the set" << endl;
			return 1;
		}

		vector<Rational> v;
		for (auto x : rs) {
			v.push_back(x);
		}
		if (v != vector<Rational>{ { 1, 25 }, { 1, 2 }, { 3, 4 }}) {
			cout << "Rationals comparison works incorrectly" << endl;
			return 2;
		}
	}

	{
		map<Rational, int> count;
		++count[{1, 2}];
		++count[{1, 2}];

		++count[{2, 3}];

		if (count.size() != 2) {
			cout << "Wrong amount of items in the map" << endl;
			return 3;
		}
	}

	cout << "OK" << endl;
	return 0;
}
