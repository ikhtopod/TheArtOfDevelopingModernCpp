#include <algorithm>
#include <vector>
#include <string>

class SortedStrings {
private:
	std::vector<std::string> m_strings {};

public:
	void AddString(const std::string& s) {
		m_strings.push_back(s);
	}

	std::vector<std::string> GetSortedStrings() {
		std::sort(std::begin(m_strings), std::end(m_strings));
		return m_strings;
	}
};
