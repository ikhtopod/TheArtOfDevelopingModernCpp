#include <stdexcept>
#include <iterator>
#include <vector>

template<typename T>
class Deque {
private:
	std::vector<T> m_head {};
	std::vector<T> m_tail {};

public:
	Deque() = default;

	T& operator[](size_t index) {
		if (index < m_head.size()) {
			return *std::next(std::rbegin(m_head), index);
		} else {
			return m_tail[index - m_head.size()];
		}
	}

	const T& operator[](size_t index) const {
		if (index < m_head.size()) {
			return *std::next(std::rbegin(m_head), index);
		} else {
			return m_tail[index - m_head.size()];
		}
	}

	T& At(size_t index) {
		if (index >= Size()) {
			throw std::out_of_range { "" };
		}

		return (*this)[index];
	}

	const T& At(size_t index) const {
		if (index >= Size()) {
			throw std::out_of_range { "" };
		}

		return (*this)[index];
	}

	bool Empty() const {
		return m_head.empty() && m_tail.empty();
	}

	size_t Size() const {
		return m_head.size() + m_tail.size();
	}

	T& Front() {
		return m_head.empty() ? m_tail.front() : m_head.back();
	}

	const T& Front() const {
		return m_head.empty() ? m_tail.front() : m_head.back();
	}

	T& Back() {
		return m_tail.empty() ? m_head.front() : m_tail.back();
	}

	const T& Back() const {
		return m_tail.empty() ? m_head.front() : m_tail.back();
	}

	void PushFront(const T& element) {
		m_head.push_back(element);
	}

	void PushBack(const T& element) {
		m_tail.push_back(element);
	}
};
