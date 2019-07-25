#pragma once

#include <string>

#include "date.h"

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
	bool Evaluate(Date, std::string);
};

class EmptyNode {

};

class DateComparisonNode {

};

class EventComparisonNode {

};

class LogicalOperationNode {

};
