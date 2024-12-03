#ifndef BANKER_HPP
#define BANKER_HPP

#include <vector>
#include <random>
#include <iostream>
#include <memory>

#include "Button.h"
#include "Case.h"

class Banker {
private:
    std::vector<double> offersHistory;
    std::shared_ptr<Button> rejectButton;
    std::shared_ptr<Button> acceptButton;
    sf::Font font;

public:
    Banker();
    Banker(const Banker &other) = default;
    Banker &operator=(const Banker &other) = default;
    ~Banker() = default;

    friend std::ostream& operator<<(std::ostream &os, const Banker &b);
    double offer(const std::vector<Case>& remainingCases);
    void clearOffers();
    void draw(sf::RenderWindow &window);
    void drawOffers(sf::RenderWindow &window);
    bool isAcceptButtonClicked(const sf::RenderWindow& window) const;
    bool isRejectButtonClicked(const sf::RenderWindow &window) const;
};

#endif // BANKER_HPP
