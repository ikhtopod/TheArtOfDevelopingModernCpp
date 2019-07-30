#include "test_runner.h"

namespace ru::lifanoff::utest {

void Assert(bool b, const std::string& hint) {
	AssertEqual(b, true, hint);
}

TestRunner::~TestRunner() {
	if (this->m_failCounter > 0) {
		std::cout << this->m_failCounter << " unit tests failed. Terminate";
		exit(EXIT_FAILURE);
	}
}

}//! namespace ru::lifanoff::utest
