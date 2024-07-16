// Kapselung von chrono
// Bereitstellung kleiner Methoden für Zeitabfragen

#include "time.hpp"
#include "kitti_random.hpp"

void Time::timeDelay(float duration) {
    std::this_thread::sleep_for(std::chrono::duration<float>(duration));
}

void Time::randomTimeDelay(float min, float max) {
    float duration = KittiRandom::selectFloatRandom(min, max);
    timeDelay(duration);
}

void Time::timeMeasureBegin() {
    startTime = std::chrono::high_resolution_clock::now();
}

float Time::timeMeasureEnd() {
    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed = endTime - startTime;
    return elapsed.count();
}
