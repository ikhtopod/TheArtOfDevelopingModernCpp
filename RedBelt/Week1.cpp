#include <iostream>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <vector>
#include <chrono>
#include <string>


template<typename Iterator>
class RangeIterator {
private:
	Iterator m_begin;
	Iterator m_end;

public:
	RangeIterator(Iterator begin, Iterator end) : m_begin(begin), m_end(end) {}

	Iterator begin() const {
		return m_begin;
	}

	Iterator end() const {
		return m_end;
	}
};

template <typename T>
RangeIterator<typename std::vector<T>::iterator> Head0(std::vector<T>& v_str, size_t amount) {
	return RangeIterator<std::vector<T>::iterator> {
		std::begin(v_str), std::next(std::begin(v_str), std::min(amount, v_str.size()))
	};
}

template <typename T>
std::vector<T> Head1(const std::vector<T>& v_str, size_t amount) {
	if (amount > v_str.size()) {
		amount = v_str.size();
	}

	std::vector<T> result(amount);
	std::copy_n(std::cbegin(v_str), amount, std::begin(result));

	return result;
}

template <typename T>
std::vector<T> Head2(const std::vector<T>& v_str, size_t amount) {
	return std::vector<T> {
		std::begin(v_str),
			std::next(std::begin(v_str),
					  std::min<size_t>(amount, v_str.size())
			)
	};
}

template <typename Func>
void RunTestHead(Func Head, size_t count) {
	using namespace std::chrono;
	std::vector<std::string> v_str {
		"Zero", "One", "Two", "Three",
		"Four", "Five", "Six", "Seven",
	};

	time_point<steady_clock> start_time = steady_clock::now();
	for (size_t i = 0; i < count; ++i) {
		auto str = Head(v_str, 3);
	}
	time_point<steady_clock> finish_time = steady_clock::now();

	nanoseconds result = finish_time - start_time;
	std::cout << "Count: " << count << std::endl;
	std::cout << "Result: " << result.count() << " ns" << std::endl;
	std::cout << "        " << duration_cast<microseconds>(result).count() << " ms" << std::endl;
	std::cout << "        " << duration_cast<milliseconds>(result).count() << " us" << std::endl;
	std::cout << "        " << duration_cast<duration<double, std::ratio<1, 1>>>(result).count() << " s" << std::endl << std::endl;
}

#define HEAD(head, count) {								\
	std::cout << #head ## "<std::string>" << std::endl;	\
	RunTestHead(head<std::string>, count);				\
}

void RunTimeTest(size_t count) {
	HEAD(Head0, count);
	HEAD(Head1, count);
	HEAD(Head2, count);
}

int main() {
	std::vector<std::string> v_str {
		"Zero", "One", "Two", "Three",
		"Four", "Five", "Six", "Seven",
	};

	for (const auto& str : v_str) {
		std::cout << str << std::endl;
	}

	std::cout << std::endl;

	for (const auto& str : Head0<std::string>(v_str, 3)) {
		std::cout << str << std::endl;
	}

	std::cout << std::endl;

	for (const auto& str : Head1<std::string>(v_str, 3)) {
		std::cout << str << std::endl;
	}


	std::cout << std::endl;

	for (const auto& str : Head2<std::string>(v_str, 3)) {
		std::cout << str << std::endl;
	}

	std::cout << std::endl;

	std::vector<size_t> counts {};
	for (size_t i = 1; i <= 1'000'000; i *= 10) {
		counts.push_back(i);
	}

	/*for (const auto& count : counts) {
		RunTimeTest(count);
	}*/

	return 0;
}
