#include <algorithm>
#include <vector>

const char OPERATION_ADD = '+';
const char OPERATION_SUB = '-';
const char OPERATION_MUL = '*';
const char OPERATION_DIV = '/';

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
		double result = 0.0;

		if (m_operation == OPERATION_ADD) {
			result = value + m_value;
		} else if (m_operation == OPERATION_SUB) {
			result = value - m_value;
		} else if (m_operation == OPERATION_MUL) {
			result = value * m_value;
		} else if (m_operation == OPERATION_DIV) {
			result = value / m_value;
		}

		return result;
	}

	void Invert() {
		if (m_operation == OPERATION_ADD) {
			m_operation = OPERATION_SUB;
		} else if (m_operation == OPERATION_SUB) {
			m_operation = OPERATION_ADD;
		} else if (m_operation == OPERATION_MUL) {
			m_operation = OPERATION_DIV;
		} else if (m_operation == OPERATION_DIV) {
			m_operation = OPERATION_MUL;
		}
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
