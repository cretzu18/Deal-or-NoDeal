#ifndef RANDOMUTIL_H
#define RANDOMUTIL_H

#include <random>

class RandomUtil {
public:
    static int getRandomInt(int min, int max);
    static double getRandomDouble(double min, double max);
};

#endif //RANDOMUTIL_H
