#include "profiler.h"

using namespace std::chrono;

LogDuration::LogDuration(const std::string& message) :
	m_start(steady_clock::now()), m_message(message) {}

LogDuration::~LogDuration() {
	time_point<steady_clock> finish = steady_clock::now();
	nanoseconds dur_nano = finish - m_start;

	milliseconds dur_milli = duration_cast<milliseconds>(dur_nano);
	DoubleSecond dur_second_double = duration_cast<DoubleSecond>(dur_nano);

	std::cerr << m_message << ": " << dur_second_double.count() << "s (" <<
		dur_milli.count() << " ms)" << std::endl;
}
