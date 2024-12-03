#ifndef CASE_HPP
#define CASE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Errors.h"

class Case {
private:
    double amount;
    bool selected;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Text text;
    sf::Font font;

public:
    explicit Case(double money = 0);
    Case(const Case &other);
    Case& operator=(const Case &other);
    ~Case() = default;

    friend std::ostream &operator<<(std::ostream &os, const Case &c);
    void selectCase();
    void deselectCase();
    bool isSelected() const;
    void eliminateCase();
    bool isEliminated() const;
    void setPositionText();
    void draw(sf::RenderWindow &window) const;
    void setPosition(float x, float y);
    bool isMouseOver(const sf::RenderWindow& window) const;
    bool isClicked(const sf::RenderWindow& window) const;
    [[nodiscard]] double getAmount() const;
};

#endif // CASE_HPP
