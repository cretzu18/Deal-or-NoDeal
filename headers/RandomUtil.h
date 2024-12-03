#ifndef RANDOMUTIL_H
#define RANDOMUTIL_H

#include <random>

/**
 * @class RandomUtil
 * @brief A utility class for generating random numbers.
 *
 * This class provides static methods to generate random integers and floating-point
 * numbers within a specified range.
 */
class RandomUtil {
public:
    /**
     * @brief Generates a random integer within the specified range.
     *
     * @param min The minimum possible value for the generated random integer.
     * @param max The maximum possible value for the generated random integer.
     * @return A random integer in the range [min, max].
     */
    [[nodiscard]] static int getRandomInt(int min, int max);

    /**
     * @brief Generates a random double within the specified range.
     *
     * This method generates a random floating-point number in the range from `min` to `max`.
     * It uses the random number generator to return a uniformly distributed double.
     *
     * @param min The minimum possible value for the generated random double.
     * @param max The maximum possible value for the generated random double.
     * @return A random double in the range [min, max].
     */
    [[nodiscard]] static double getRandomDouble(double min, double max);
};

#endif //RANDOMUTIL_H
