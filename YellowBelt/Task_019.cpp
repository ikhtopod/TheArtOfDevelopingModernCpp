#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> SplitIntoWords(const std::string& s) {
	std::vector<std::string> result {};

	auto begin_word = std::begin(s);
	const auto& end_s = std::cend(s);

	while (true) {
		auto end_word = std::find(begin_word, end_s, ' ');
		result.push_back(std::string { begin_word, end_word });

		if (end_word == end_s) break;

		begin_word = end_word + 1;
	}

	return result;
}

int main() {
	using namespace std;

	string s = "C Cpp Java Python";

	vector<string> words = SplitIntoWords(s);
	cout << words.size() << " ";
	for (auto it = begin(words); it != end(words); ++it) {
		if (it != begin(words)) {
			cout << "/";
		}
		cout << *it;
	}
	cout << endl;

	return 0;
}
