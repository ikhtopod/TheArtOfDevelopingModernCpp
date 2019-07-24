#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Person {
public:
	string m_name;
	string m_profession;

public:
	explicit Person(const std::string& name, const std::string& profession) :
		m_name(name), m_profession(profession) {}

	virtual void Walk(const string& destination) const {
		cout << m_profession << ": " << m_name << " walks to: " << destination << endl;
	}
};


class Student : public Person {
public:
	string m_favouriteSong;

public:
	explicit Student(const string& name, string favouriteSong) :
		Person(name, "Student"), m_favouriteSong(favouriteSong) {}

	void Learn() const {
		cout << m_profession << ": " << m_name << " learns" << endl;
	}

	void SingSong() const {
		cout << m_profession << ": " << m_name << " sings a song: " << m_favouriteSong << endl;
	}

	virtual void Walk(const string& destination) const override {
		Person::Walk(destination);
		SingSong();
	}
};


class Teacher : public Person {
public:
	string m_subject;

public:
	explicit Teacher(const string& name, const string& subject) :
		Person(name, "Teacher"), m_subject(subject) {}

	void Teach() const {
		cout << m_profession << ": " << m_name << " teaches: " << m_subject << endl;
	}
};


class Policeman : public Person {
public:
	explicit Policeman(const string& name) : Person(name, "Policeman") {}

	void Check(const Person& h) const {
		cout << m_profession << ": " << m_name << " checks " << h.m_profession << ". " <<
			h.m_profession << "'s name is: " << h.m_name << endl;
	}
};


void VisitPlaces(const Person& t, const vector<string>& places) {
	for (const auto& p : places) {
		t.Walk(p);
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
