#include <cstdlib>
#include <iostream>
#include <numeric>
#include <iterator>
#include <vector>
#include <string>
#include <utility>

enum class ArithmeticOperator : uint8_t {
	NONE,
	MUL, DIV,
	ADD, SUB,
};

class ArithmeticExpression {
private:
	std::vector<std::pair<ArithmeticOperator, int>> m_operations {};
	std::string m_expression {};

private:
	void Generate() {
		m_expression = std::to_string(m_operations.front().second);

		for (auto it = std::next(std::begin(m_operations)); it != std::end(m_operations); std::advance(it, 1)) {
			auto prev_it = std::prev(it);

			if (it->first <= prev_it->first) {
				m_expression = std::string("(") + m_expression + ")";
			}

			m_expression += std::string(" ") + GetCharByArithmeticOperator(it->first) + " " + std::to_string(it->second);
		}
	}

	static ArithmeticOperator GetArithmeticOperatorByChar(char c) {
		switch (c) {
			case '*':
				return ArithmeticOperator::MUL;
			case '/':
				return ArithmeticOperator::DIV;
			case '+':
				return ArithmeticOperator::ADD;
			case '-':
				return ArithmeticOperator::SUB;
			default:
				return ArithmeticOperator::NONE;
		}
	}

	static char GetCharByArithmeticOperator(ArithmeticOperator ao) {
		switch (ao) {
			case ArithmeticOperator::MUL:
				return '*';
			case ArithmeticOperator::DIV:
				return '/';
			case ArithmeticOperator::ADD:
				return '+';
			case ArithmeticOperator::SUB:
				return '-';
			default:
				return ' ';
		}
	}

public:
	ArithmeticExpression(int operation) {
		AddOperation(operation);
	}

	void AddOperation(int number) {
		AddOperation(ArithmeticOperator::NONE, number);
	}

	void AddOperation(char operator_, int number) {
		AddOperation(GetArithmeticOperatorByChar(operator_), number);
	}

	void AddOperation(ArithmeticOperator ao, int number) {
		m_operations.push_back(std::pair { ao, number });
		Generate();
	}

	std::string GetExpression() const {
		return m_expression;
	}
};


int main() {
	int x;
	size_t n = 0;
	std::cin >> x >> n;

	ArithmeticExpression ae { x };

	for (size_t i = 0; i < n; ++i) {
		char c; int num;
		std::cin >> c >> num;

		ae.AddOperation(c, num);
	}

	std::cout << ae.GetExpression() << std::endl;

	return EXIT_SUCCESS;
}
