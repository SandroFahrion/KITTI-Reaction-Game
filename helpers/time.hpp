#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>
#include <thread>

class Time {
public:
    static void timeDelay(float duration);
    static void randomTimeDelay(float min, float max);
    void timeMeasureBegin();
    float timeMeasureEnd();

private:
    std::chrono::high_resolution_clock::time_point startTime;
};

#endif // TIME_HPP
