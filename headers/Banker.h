#ifndef BANKER_HPP
#define BANKER_HPP

#include <vector>
#include <random>
#include <iostream>
#include "Case.h"

class Banker {
private:
    double currentOffer;
    std::vector<double> offersHistory;

public:
    Banker();
    Banker(const Banker &other) = default;
    Banker &operator=(const Banker &other) = default;
    ~Banker() = default;

    friend std::ostream& operator<<(std::ostream &os, const Banker &b);
    // momentan nu folosesc functia offer
    // void offer(const std::vector<Case>& remainingCases);
};

#endif // BANKER_HPP
