#include "Banker.h"

Banker::Banker() : currentOffer(0) {}

std::ostream& operator<<(std::ostream &os, const Banker &b) {
    os << "The banker offered " << b.currentOffer << "$.\n";
    return os;
}

void Banker::offer(const std::vector<Case>& remainingCases) {
    if (remainingCases.empty()) return;

    double totalAmount = 0;
    for (const Case& c : remainingCases) {
        totalAmount += c.getAmount();
    }

    const double average = totalAmount / static_cast<double>(remainingCases.size());
    const double minAmount = average * 0.75;
    const double maxAmount = average * 1.1;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(minAmount, maxAmount);
    currentOffer = dis(gen);

    offersHistory.push_back(currentOffer);
}
