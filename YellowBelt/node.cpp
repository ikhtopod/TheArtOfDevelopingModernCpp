#include "node.h"

/* Node */

bool Node::Evaluate(const Date& date, const std::string& event) {
	return Evaluate(date, Event { event });
}


/* EmptyNode */

bool EmptyNode::Evaluate(const Date& date, const Event& event) {
	return true;
}


/* DateComparisonNode */

DateComparisonNode::DateComparisonNode(const Comparison& comparison, const Date& date) :
	m_comparison(comparison), m_date(date) {}

bool DateComparisonNode::Evaluate(const Date& date, const Event& event) {
	return ComparisonEvaluate<Date>(date, m_comparison, m_date);
}


/* EventComparisonNode */

EventComparisonNode::EventComparisonNode(const Comparison& comparison, const std::string& event) :
	EventComparisonNode(comparison, Event { event }) {}


EventComparisonNode::EventComparisonNode(const Comparison& comparison, const Event& event) :
	m_comparison(comparison), m_event(event) {}

bool EventComparisonNode::Evaluate(const Date& date, const Event& event) {
	return ComparisonEvaluate<Event>(event, m_comparison, m_event);
}


/* LogicalOperationNode */

LogicalOperationNode::LogicalOperationNode(const LogicalOperation& op, const std::shared_ptr<Node>& left, const std::shared_ptr<Node>& right) :
	m_op(op), m_left(left), m_right(right) {}

bool LogicalOperationNode::Evaluate(const Date& date, const Event& event) {
	switch (m_op) {
		case LogicalOperation::Or:
			return m_left->Evaluate(date, event) || m_right->Evaluate(date, event);
		case LogicalOperation::And:
			return m_left->Evaluate(date, event) && m_right->Evaluate(date, event);
		default:
			return false;
	}
}
