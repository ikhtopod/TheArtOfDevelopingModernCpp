#include <string>
#include <algorithm>

class ReversibleString {
private:
	std::string m_string {};
public:
	ReversibleString() = default;
	ReversibleString(std::string str);

	void Reverse();
	std::string ToString() const;
};

ReversibleString::ReversibleString(std::string str) {
	m_string = str;
}

void ReversibleString::Reverse() {
	std::reverse(std::begin(m_string), std::end(m_string));
}

std::string ReversibleString::ToString() const {
	return m_string;
}
