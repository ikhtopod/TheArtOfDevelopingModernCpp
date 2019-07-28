#pragma once

#include <string>
#include <memory>

#include "date.h"
#include "event.h"

enum class Comparison {
	NotEqual, Equal,
	Less, LessOrEqual,
	Greater, GreaterOrEqual,
};

enum class LogicalOperation {
	Or, And
};

template <class T>
bool ComparisonEvaluate(const T& lhs, const Comparison& comparison, const T& rhs) {
	switch (comparison) {
		case Comparison::NotEqual:
			return lhs != rhs;
		case Comparison::Equal:
			return lhs == rhs;
		case Comparison::Less:
			return lhs < rhs;
		case Comparison::LessOrEqual:
			return lhs <= rhs;
		case Comparison::Greater:
			return lhs > rhs;
		case Comparison::GreaterOrEqual:
			return lhs >= rhs;
		default:
			return false;
	}
}

class Node {
public:
	virtual bool Evaluate(const Date& date, const std::string& event);
	virtual bool Evaluate(const Date& date, const Event& event) = 0;
};

class EmptyNode : public Node {
public:
	EmptyNode() = default;

	virtual bool Evaluate(const Date& date, const Event& event) override;
};

class DateComparisonNode : public Node {
private:
	Comparison m_comparison {};
	Date m_date {};

public:
	DateComparisonNode(const Comparison& comparison, const Date& date);

	virtual bool Evaluate(const Date& date, const Event& event) override;
};

class EventComparisonNode : public Node {
private:
	Comparison m_comparison {};
	Event m_event {};

public:
	EventComparisonNode(const Comparison& comparison, const std::string& event);
	EventComparisonNode(const Comparison& comparison, const Event& event);

	virtual bool Evaluate(const Date& date, const Event& event) override;
};

class LogicalOperationNode : public Node {
private:
	LogicalOperation m_op;
	std::shared_ptr<Node> m_left, m_right;

public:
	LogicalOperationNode(const LogicalOperation& op, const std::shared_ptr<Node>& left, const std::shared_ptr<Node>& right);

	virtual bool Evaluate(const Date& date, const Event& event) override;
};
