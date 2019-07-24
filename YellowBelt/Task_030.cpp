#include <iostream>
#include <iomanip>
#include <memory>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

class Figure {
protected:
	std::string m_name {};
	double m_perimeter = 0.0;
	double m_area = 0.0;

	virtual void CalculatePerimeter() = 0;
	virtual void CalculateArea() = 0;

public:
	Figure() = default;
	Figure(std::string name) : m_name(name) {}
	virtual ~Figure() = default;

	virtual std::string Name() const = 0;
	virtual double Perimeter() const = 0;
	virtual double Area() const = 0;
};

class Circle final : public Figure {
private:
	inline static const double PI = 3.14;

private:
	double m_radius;

protected:
	virtual void CalculatePerimeter() override {
		m_perimeter = 2.0 * PI * m_radius;
	}

	virtual void CalculateArea() override {
		m_area = PI * std::pow(m_radius, 2.0);
	}

public:
	Circle(double radius) : Figure("CIRCLE"), m_radius(radius) {
		CalculatePerimeter();
		CalculateArea();
	}

	virtual std::string Name() const override {
		return m_name;
	}

	virtual double Perimeter() const override {
		return m_perimeter;
	}

	virtual double Area() const override {
		return m_area;
	}

};

class Rect final : public Figure {
private:
	double m_width, m_height;

protected:
	virtual void CalculatePerimeter() override {
		m_perimeter = 2.0 * (m_width + m_height);
	}

	virtual void CalculateArea() override {
		m_area = m_width * m_height;
	}

public:
	Rect(double width, double height) : Figure("RECT"),
		m_width(width), m_height(height) {

		CalculatePerimeter();
		CalculateArea();
	}

	virtual std::string Name() const override {
		return m_name;
	}

	virtual double Perimeter() const override {
		return m_perimeter;
	}

	virtual double Area() const override {
		return m_area;
	}
};

class Triangle final : public Figure {
private:
	double m_a, m_b, m_c;

protected:
	virtual void CalculatePerimeter() override {
		m_perimeter = m_a + m_b + m_c;
	}

	virtual void CalculateArea() override {
		double p = m_perimeter / 2.0;
		m_area = std::sqrt(p * (p - m_a) * (p - m_b) * (p - m_c));
	}

public:
	Triangle(double a, double b, double c) : Figure("TRIANGLE"),
		m_a(a), m_b(b), m_c(c) {

		CalculatePerimeter();
		CalculateArea();
	}

	virtual std::string Name() const override {
		return m_name;
	}

	virtual double Perimeter() const override {
		return m_perimeter;
	}

	virtual double Area() const override {
		return m_area;
	}
};


std::shared_ptr<Figure> CreateFigure(std::istream& is) {
	std::shared_ptr<Figure> result {};

	std::string fgrCmd {};
	double arg1 = 0.0;
	is >> fgrCmd >> arg1;

	if (fgrCmd == "CIRCLE") {
		result = std::make_shared<Circle>(arg1);
	} else {
		double arg2 = 0.0;
		is >> arg2;

		if (fgrCmd == "RECT") {
			result = std::make_shared<Rect>(arg1, arg2);
		} else {
			double arg3 = 0.0;
			is >> arg3;

			if (fgrCmd == "TRIANGLE") {
				result = std::make_shared<Triangle>(arg1, arg2, arg3);
			}//fi TRIANGLE
		}//fi RECT
	}//fi CIRCLE

	return result;
}


using namespace std;

int main() {
	vector<shared_ptr<Figure>> figures;
	for (string line; getline(cin, line); ) {
		istringstream is(line);

		string command;
		is >> command;
		if (command == "ADD") {
			figures.push_back(CreateFigure(is));
		} else if (command == "PRINT") {
			for (const auto& current_figure : figures) {
				cout << fixed << setprecision(3)
					<< current_figure->Name() << " "
					<< current_figure->Perimeter() << " "
					<< current_figure->Area() << endl;
			}
		}
	}
	return 0;
}