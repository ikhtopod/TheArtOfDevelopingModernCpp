#include <algorithm>
#include <vector>

class FunctionPart {
private:
	char m_operation;
	double m_value;

public:
	FunctionPart(char operation, double value) {
		m_operation = operation;
		m_value = value;
	}

	double Apply(double value) const {
		return m_operation == '+' ? value + m_value : value - m_value;
	}

	void Invert() {
		m_operation = m_operation == '+' ? '-' : '+';
	}
};

class Function {
private:
	std::vector<FunctionPart> m_parts;

public:
	void AddPart(char operation, double value) {
		m_parts.push_back({ operation, value });
	}

	double Apply(double value) const {
		for (const auto& p : m_parts) {
			value = p.Apply(value);
		}

		return value;
	}

	void Invert() {
		for (auto& p : m_parts) {
			p.Invert();
		}

		std::reverse(std::begin(m_parts), std::end(m_parts));
	}
};
