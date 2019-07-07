#include <string>

struct Specialization {
	std::string value;

	explicit Specialization(const std::string& _value) {
		value = _value;
	}
};

struct Course {
	std::string value;

	explicit Course(const std::string& _value) {
		value = _value;
	}
};

struct Week {
	std::string value;

	explicit Week(const std::string& _value) {
		value = _value;
	}
};

struct LectureTitle {
	std::string specialization;
	std::string course;
	std::string week;

	LectureTitle(const Specialization& _specialization,
				 const Course& _course,
				 const Week& _week) {
		specialization = _specialization.value;
		course = _course.value;
		week = _week.value;
	}
};
