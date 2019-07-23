#include <iostream>
#include <string>

using namespace std;

class Animal {
public:
	const std::string Name;

public:
	Animal(const std::string& name) : Name(name) {}
};


class Dog : public Animal {
public:
	Dog(const std::string& name) : Animal(name) {}

	void Bark() {
		std::cout << Name << " barks: woof!" << std::endl;
	}
};
