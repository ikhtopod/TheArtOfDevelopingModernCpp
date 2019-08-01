#include "test_runner.h"

#include <utility>
#include <vector>

using namespace std;

#ifdef RU_LIFANOFF_UTEST_TEST_RUNNER_H
using namespace ru::lifanoff::utest;
#endif // RU_LIFANOFF_UTEST_TEST_RUNNER_H


template<typename T>
class Table {
private:
	std::vector<std::vector<T>> m_table {};

public:
	Table(size_t first, size_t second) {
		Resize(first, second);
	}

	std::vector<T>& operator[](const size_t& idx) {
		return m_table[idx];
	}

	const std::vector<T>& operator[](const size_t& idx) const {
		return m_table[idx];
	}

	std::pair<size_t, size_t> Size() const {
		size_t first = m_table.size();
		size_t second = first == 0 ? 0 : std::begin(m_table)->size();
		return std::pair<size_t, size_t> { first, second };
	}

	void Resize(size_t first, size_t second) {
		m_table.resize(first);

		for (auto& tbl : m_table) {
			tbl.resize(second);
		}
	}
};

void TestTable() {
	Table<int> t(1, 1);
	ASSERT_EQUAL(t.Size().first, 1u);
	ASSERT_EQUAL(t.Size().second, 1u);
	t[0][0] = 42;
	ASSERT_EQUAL(t[0][0], 42);
	t.Resize(3, 4);
	ASSERT_EQUAL(t.Size().first, 3u);
	ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestTable);
	return 0;
}
