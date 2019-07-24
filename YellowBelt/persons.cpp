#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Person {
protected:
	const string m_name;
	const string m_profession;

protected:
	ostream& PrintPerson() const {
		return cout << m_profession << ": " << m_name;
	}

public:
	explicit Person(const std::string& name, const std::string& profession) :
		m_name(name), m_profession(profession) {}

	virtual void Walk(const string& destination) const {
		PrintPerson() << " walks to: " << destination << endl;
	}

	string GetName() const {
		return m_name;
	}

	string GetProfession() const {
		return m_profession;
	}
};


class Teacher : public Person {
public:
	const string m_subject;

public:
	explicit Teacher(const string& name, const string& subject) :
		Person(name, "Teacher"), m_subject(subject) {}

	void Teach() const {
		PrintPerson() << " teaches: " << m_subject << endl;
	}
};


class Policeman : public Person {
public:
	explicit Policeman(const string& name) :
		Person(name, "Policeman") {}

	void Check(const Person& h) const {
		PrintPerson() << " checks " << h.GetProfession() << ". " <<
			h.GetProfession() << "'s name is: " << h.GetName() << endl;
	}
};


class Student : public Person {
private:
	const string m_favouriteSong;

public:
	explicit Student(const string& name, string favouriteSong) :
		Person(name, "Student"), m_favouriteSong(favouriteSong) {}

	virtual void Walk(const string& destination) const override {
		Person::Walk(destination);
		SingSong();
	}

	void Learn() const {
		PrintPerson() << " learns" << endl;
	}

	void SingSong() const {
		PrintPerson() << " sings a song: " << m_favouriteSong << endl;
	}
};


void VisitPlaces(Person& p, const vector<string>& places) {
	for (const auto& place : places) {
		p.Walk(place);
	}
}


int main() {
	Teacher t { "Jim", "Math" };
	Student s { "Ann", "We will rock you" };
	Policeman p { "Bob" };

	VisitPlaces(t, { "Moscow", "London" });
	p.Check(s);
	VisitPlaces(s, { "Moscow", "London" });

	return 0;
}
