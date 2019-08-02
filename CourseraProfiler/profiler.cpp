#include "profiler.h"

using namespace std::chrono;

LogDuration::LogDuration() :
	m_start(steady_clock::now()) {}

LogDuration::~LogDuration() {
	time_point<steady_clock> finish = steady_clock::now();
	nanoseconds dur_nano = finish - m_start;
	milliseconds dur_milli = duration_cast<milliseconds>(dur_nano);
	DoubleSecond dur_second_double = duration_cast<DoubleSecond>(dur_nano);
	std::cerr << dur_milli.count() << " ms (" << dur_second_double.count() << " s)" << std::endl;
}
