#ifndef CASE_HPP
#define CASE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Case {
private:
    double amount;
    bool selected;
    sf::Sprite sprite;
    sf::Texture texture;

public:
    explicit Case(double money = 0);
    Case(const Case &other);
    Case& operator=(const Case &other);
    ~Case() = default;

    friend std::ostream &operator<<(std::ostream &os, const Case &c);
    double getAmount() const;
    void selectCase();
    void draw(sf::RenderWindow &window) const;
    void setPosition(float x, float y);
    bool isMouseOver(const sf::RenderWindow& window) const;
    bool isClicked(const sf::RenderWindow& window) const;
};

#endif // CASE_HPP
