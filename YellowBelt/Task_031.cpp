#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human {
public:
	string m_name;

public:
	Human(const std::string& name) : m_name(name) {}

	virtual void Walk(const string& destination) const = 0;
};

class Student : public Human {
public:
	string m_favouriteSong;

public:
	Student(const string& name, string favouriteSong) :
		Human(name), m_favouriteSong(favouriteSong) {}

	void Learn() {
		cout << "Student: " << m_name << " learns" << endl;
	}

	void SingSong() {
		cout << "Student: " << m_name << " sings a song: " << m_favouriteSong << endl;
	}

	virtual void Walk(const string& destination) const {
		cout << "Student: " << m_name << " walks to: " << destination << endl;
		cout << "Student: " << m_name << " sings a song: " << m_favouriteSong << endl;
	}
};


class Teacher : public Human {
public:
	string m_subject;

public:
	Teacher(const string& name, string subject) :
		Human(name), m_subject(subject) {}

	void Teach() {
		cout << "Teacher: " << m_name << " teaches: " << m_subject << endl;
	}

	virtual void Walk(const string& destination) const {
		cout << "Teacher: " << m_name << " walks to: " << destination << endl;
	}
};


class Policeman : public Human {
public:
	Policeman(const string& name) : Human(name) {}

	void Check(Teacher t) {
		cout << "Policeman: " << m_name << " checks Teacher. Teacher's name is: " << t.m_name << endl;
	}

	void Check(Student s) {
		cout << "Policeman: " << m_name << " checks Student. Student's name is: " << s.m_name << endl;
	}

	void Check(Policeman p) {
		cout << "Policeman: " << m_name << " checks Policeman. Policeman's name is: " << p.m_name << endl;
	}

	virtual void Walk(const string& destination) const {
		cout << "Policeman: " << m_name << " walks to: " << destination << endl;
	}
};


void VisitPlaces(const Human& t, const vector<string>& places) {
	for (auto p : places) {
		t.Walk(p);
	}
}

int main() {
	Teacher t("Jim", "Math");
	Student s("Ann", "We will rock you");
	Policeman p("Bob");

	VisitPlaces(t, { "Moscow", "London" });
	p.Check(s);
	VisitPlaces(s, { "Moscow", "London" });
	return 0;
}
