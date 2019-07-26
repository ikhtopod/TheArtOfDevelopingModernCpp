#include "node.h"

bool Node::Evaluate(Date date, std::string event) {
	return Evaluate(date, Event { event });
}
