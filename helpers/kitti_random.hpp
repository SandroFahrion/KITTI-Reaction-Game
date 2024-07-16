#ifndef KITTI_RANDOM_HPP
#define KITTI_RANDOM_HPP

#include <random>

class KittiRandom {
public:
    static float selectFloatRandom(float min, float max);
    static int selectIntRandom(int min, int max);
};

#endif // KITTI_RANDOM_HPP
