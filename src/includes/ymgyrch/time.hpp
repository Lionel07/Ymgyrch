#pragma once

#define TIME_IMP_CHRONO 1
#define TIME_IMP_WIN 2

#define TIME_IMP TIME_IMP_CHRONO

#if TIME_IMP == TIME_IMP_CHRONO
#include <chrono>
#endif

namespace Ymgyrch {
class Time {
public:
    static void reset();
    static double getElapsed();
private:
#if TIME_IMP == TIME_IMP_CHRONO
    static std::chrono::high_resolution_clock::time_point _timestamp;
 #endif
};
}; // namespace Ymgyrch
