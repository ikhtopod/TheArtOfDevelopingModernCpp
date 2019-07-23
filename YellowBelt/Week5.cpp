#include <iostream>

class Base {
public:
	virtual void Print() const {
		std::cout << "Base" << std::endl;
	}
};

class Derived : public Base {
public:
	void Print() const override {
		std::cout << "Derived" << std::endl;
	}
};

int main() {
	Derived d {};
	d.Print();

	Base b {};
	b.Print();

	Base* bd = new Derived {};
	bd->Print();
	delete bd;

	return 0;
}
