#include <algorithm>
#include <string>
#include <vector>
#include <set>

using namespace std;

class Learner {
private:
	set<string> dict;

public:
	int Learn(const vector<string>& words) {
		int newWords = 0;

		for (const auto& word : words) {
			if (dict.count(word) == 0) {
				++newWords;
				dict.insert(word);
			}
		}

		return newWords;
	}

	vector<string> KnownWords() {
		return vector<string> { std::begin(dict), std::end(dict) };
	}
};

#include <iostream>
#include <sstream>
#include "profile.h"

int main() {
	LOG_DURATION("Learner");

	Learner learner;
	string line { " abcdef " };

	do {
		vector<string> words;
		stringstream ss(line);
		string word;
		while (ss >> word) {
			words.push_back(word);
		}
		//cout << learner.Learn(words) << "\n";
		learner.Learn(words);
	} while (next_permutation(std::begin(line), std::end(line)));

	cout << "=== known words ===\n";
	cout << learner.KnownWords().size() << "\n";
	//for (auto word : learner.KnownWords()) {
	//	cout << word << "\n";
	//}
}
