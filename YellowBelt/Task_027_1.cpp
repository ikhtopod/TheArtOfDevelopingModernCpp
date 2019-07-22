#include <cstdlib>
#include <iostream>
#include <numeric>
#include <iterator>
#include <vector>
#include <string>
#include <utility>
#include <stack>

enum class ArithmeticOperator : uint8_t {
	NONE,
	MUL, DIV,
	ADD, SUB,
};

struct Operation {
	ArithmeticOperator oper = ArithmeticOperator::NONE;
	int number = 0;
};

class ArithmeticExpression {
private:
	std::stack<Operation> m_operations {};
	std::string m_expression {};

private:
	void NextGenerate() {
		m_expression = std::string("(") + m_expression + ") " +
			GetCharByArithmeticOperator(m_operations.top().oper) +
			" " + std::to_string(m_operations.top().number);
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
		m_operations.push(Operation { ArithmeticOperator::NONE, operation });
		m_expression = std::to_string(m_operations.top().number);
	}

	void AddOperation(char operator_, int number) {
		AddOperation(GetArithmeticOperatorByChar(operator_), number);
	}

	void AddOperation(ArithmeticOperator ao, int number) {
		m_operations.push(Operation { ao, number });
		NextGenerate();
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
