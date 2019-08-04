#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>

using namespace std;

class ReadingManager {
private:
	static const int MAX_USER_COUNT = 100'000;

	vector<int> m_userPageCounts;
	vector<int> m_sortedUsers;   // отсортированы по убыванию количества страниц
	vector<int> m_userPositions; // позиции в векторе sorted_users_

private:
	int GetUserCount() const {
		return m_sortedUsers.size();
	}

	void AddUser(int user_id) {
		m_sortedUsers.push_back(user_id);
		m_userPositions[user_id] = m_sortedUsers.size() - 1;
	}

	void SwapUsers(int lhs_position, int rhs_position) {
		const int lhs_id = m_sortedUsers[lhs_position];
		const int rhs_id = m_sortedUsers[rhs_position];
		swap(m_sortedUsers[lhs_position], m_sortedUsers[rhs_position]);
		swap(m_userPositions[lhs_id], m_userPositions[rhs_id]);
	}

public:
	ReadingManager() :
		m_userPageCounts(MAX_USER_COUNT + 1, 0),
		m_sortedUsers(),
		m_userPositions(MAX_USER_COUNT + 1, -1) {}

	void Read(int user_id, int page_count) { // need O(1)
		if (m_userPageCounts[user_id] == 0) {
			AddUser(user_id);
		}

		m_userPageCounts[user_id] = page_count;

		int& position = m_userPositions[user_id];
		while (position > 0 && page_count > m_userPageCounts[m_sortedUsers[position - 1]]) {
			SwapUsers(position, position - 1);
		}
	}

	double Cheer(int user_id) const { // need O(M), m = page_count
		if (m_userPageCounts[user_id] == 0) {
			return 0;
		}

		const int user_count = GetUserCount();
		if (user_count == 1) {
			return 1;
		}

		const int page_count = m_userPageCounts[user_id];
		int position = m_userPositions[user_id];
		while (position < user_count &&
			m_userPageCounts[m_sortedUsers[position]] == page_count) {
			++position;
		}

		if (position == user_count) {
			return 0;
		}

		const double user_count_d = static_cast<double>(user_count);

		return (user_count_d - position) / (user_count_d - 1.0);
	}
};


int main1() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ReadingManager manager;

	int query_count;
	cin >> query_count;

	for (int query_id = 0; query_id < query_count; ++query_id) {
		string query_type;
		cin >> query_type;
		int user_id;
		cin >> user_id;

		if (query_type == "READ") {
			int page_count;
			cin >> page_count;
			manager.Read(user_id, page_count);
		} else if (query_type == "CHEER") {
			cout << setprecision(6) << manager.Cheer(user_id) << "\n";
		}
	}

	return 0;
}


#include <sstream>
#include "profile.h"

int main() {
	ios::sync_with_stdio(false);
	istringstream::sync_with_stdio(false);

	cin.tie(nullptr);

	istringstream istr { "CHEER 5 READ 1 10 CHEER 1 READ 2 5 READ 3 7 CHEER 2 CHEER 3 READ 3 10 CHEER 3 READ 3 11 CHEER 3 CHEER 1 " };
	istr.tie(nullptr);

	int query_count = 12;

	ReadingManager manager1;
	for (int query_id = 0; query_id < query_count; ++query_id) {
		string query_type;
		istr >> query_type;
		int user_id;
		istr >> user_id;

		if (query_type == "READ") {
			int page_count;
			istr >> page_count;
			manager1.Read(user_id, page_count);
		} else if (query_type == "CHEER") {
			cout << setprecision(6) << manager1.Cheer(user_id) << "\n";
		}
	}

	int query_count_offset = 83'333;

	
	{
		ostringstream ostr {};
		for (int qco = 0; qco < query_count * query_count_offset; ++qco) {
			ostr << "CHEER 5 READ 1 10 CHEER 1 READ 2 5 READ 3 7 CHEER 2 CHEER 3 READ 3 10 CHEER 3 READ 3 11 CHEER 3 CHEER 1 ";
		}
		istr.str(ostr.str());
		istr.clear();
	}

	ReadingManager manager;

	LOG_DURATION("Chrono Test");
	for (int qco = 0; qco < query_count_offset; ++qco) {
		for (int query_id = 0; query_id < query_count; ++query_id) {
			string query_type;
			istr >> query_type;
			int user_id;
			istr >> user_id;

			if (query_type == "READ") {
				int page_count;
				istr >> page_count;
				manager.Read(user_id, page_count);
			} else if (query_type == "CHEER") {
				//cout << setprecision(6) << manager.Cheer(user_id) << "\n";
				manager.Cheer(user_id);
			}
		}
	}

	return 0;
}
