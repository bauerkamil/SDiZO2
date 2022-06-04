#pragma once
#include <chrono>
class Timer
{
public:
	std::chrono::high_resolution_clock::time_point startTime;
	std::chrono::high_resolution_clock::time_point endTime;

	void start();
	void stop();
	long result();
};
