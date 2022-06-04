#include "../../Headers/utils/Timer.h"

void Timer::start()
{
	this->startTime = std::chrono::high_resolution_clock::now();
}

void Timer::stop()
{
	this->endTime = std::chrono::high_resolution_clock::now();
}

long Timer::result()
{
	return std::chrono::duration_cast<std::chrono::microseconds>(this->endTime - this->startTime).count();
}