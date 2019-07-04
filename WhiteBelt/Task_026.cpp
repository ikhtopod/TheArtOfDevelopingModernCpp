#include <iostream>
#include <string>
#include <map>
#include <set>

const std::string COUNT { "COUNT" };
const std::string CHECK { "CHECK" };
const std::string ADD { "ADD" };

int main() {
	int q = 0;
	std::cin >> q;

	std::map<std::string, std::set<std::string>> synonyms {};

	for (int i = 0; i < q; ++i) {
		std::string operation, word1;
		std::cin >> operation >> word1;

		if (operation == COUNT) {
			std::cout << synonyms[word1].size() << std::endl;
		} else {
			std::string word2 {};
			std::cin >> word2;

			if (operation == CHECK) {
				std::cout
					<< (synonyms[word1].find(word2) != std::cend(synonyms[word1]) ? "YES" : "NO")
					<< std::endl;
			} else if (operation == ADD) {
				synonyms[word1].insert(word2);
				synonyms[word2].insert(word1);
			}//fi
		}//fi
	}//rof

	return 0;
}
