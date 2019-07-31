#include "test_runner.h"

#include <ostream>

using namespace std;

#ifdef RU_LIFANOFF_UTEST_TEST_RUNNER_H
using namespace ru::lifanoff::utest;
#endif

#define PRINT_VALUES(out, x, y) out << (x) << endl << (y) << endl

int main() {
	TestRunner tr;
	tr.RunTest([]() {
		ostringstream output;
		PRINT_VALUES(output, 5, "red belt");
		ASSERT_EQUAL(output.str(), "5\nred belt\n");
			   }, "PRINT_VALUES usage example");

}
