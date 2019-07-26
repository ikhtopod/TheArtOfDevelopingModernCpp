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

class Node {
public:
	bool Evaluate(Date date, std::string event);
	bool Evaluate(Date date, Event event);
};

class EmptyNode : public Node {
public:
	EmptyNode() = default;
};

class DateComparisonNode : public Node {
public:
	DateComparisonNode(Comparison, Date);
};

class EventComparisonNode : public Node {
public:
	EventComparisonNode(Comparison, std::string);
};

class LogicalOperationNode : public Node {
public:
	LogicalOperationNode(LogicalOperation, std::shared_ptr<Node>, std::shared_ptr<Node>);
};
