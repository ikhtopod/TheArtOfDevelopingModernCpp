#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

class RouteManager {
private:
	map<int, set<int>> m_reachableLists;

public:
	void AddRoute(const int& start, const int& finish) {
		m_reachableLists[start].insert(finish);
		m_reachableLists[finish].insert(start);
	}

	int FindNearestFinish(int start, int finish) const {
		int result = abs(start - finish);
		if (m_reachableLists.count(start) < 1) {
			return result;
		}

		const set<int>& reachable_stations = m_reachableLists.at(start);
		if (!reachable_stations.empty()) {
			auto nearest_more = reachable_stations.lower_bound(finish);

			if (nearest_more == reachable_stations.begin()) {
				result = min(result, abs(*nearest_more - finish));
			} else if (nearest_more == reachable_stations.end()) {
				auto nearest_less = prev(nearest_more);
				result = min(result, abs(*nearest_less - finish));
			} else {
				auto nearest_less = prev(nearest_more);
				result = min(result,
							 min(abs(*nearest_more - finish),
							 abs(*nearest_less - finish))
				);
			}
		}

		return result;
	}
};

int main() {
	cin.tie(nullptr);

	RouteManager routes;

	int query_count;
	cin >> query_count;

	for (int query_id = 0; query_id < query_count; ++query_id) {
		string query_type;
		cin >> query_type;
		int start, finish;
		cin >> start >> finish;
		if (query_type == "ADD") {
			routes.AddRoute(start, finish);
		} else if (query_type == "GO") {
			cout << routes.FindNearestFinish(start, finish) << "\n";
		}
	}

	return 0;
}
