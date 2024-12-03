#ifndef RANDOMUTIL_H
#define RANDOMUTIL_H

#include <random>

class RandomUtil {
public:
    [[nodiscard]] static int getRandomInt(int min, int max);
    [[nodiscard]] static double getRandomDouble(double min, double max);
};

#endif //RANDOMUTIL_H
