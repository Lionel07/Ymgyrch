#include <ymgyrch/time.hpp>

#if TIME_IMP == TIME_IMP_CHRONO
#include <chrono>
std::chrono::high_resolution_clock::time_point Ymgyrch::Time::_timestamp;
#endif

#ifndef TIME_IMP
#error No time implementation selected.
#endif

void Ymgyrch::Time::reset() {
#if TIME_IMP == TIME_IMP_CHRONO
	_timestamp = std::chrono::high_resolution_clock::now();
#endif
}
double Ymgyrch::Time::getElapsed() {
#if TIME_IMP == TIME_IMP_CHRONO
	std::chrono::duration<double> fs = std::chrono::high_resolution_clock::now() - _timestamp;
	return fs.count();
#endif
}
