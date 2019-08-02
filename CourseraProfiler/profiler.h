#pragma once

#ifndef COURSERAPROFILER_PROFILE_H
#define COURSERAPROFILER_PROFILE_H

#include <iostream>
#include <string>
#include <ratio>
#include <chrono>

class LogDuration final {
	using DoubleSecond = std::chrono::duration<double, std::ratio<1, 1>>;

private:
	std::chrono::steady_clock::time_point m_start;
	std::string m_message;

public:
	explicit LogDuration(const std::string& message);
	~LogDuration();
};


#endif // !COURSERAPROFILER_PROFILE_H
