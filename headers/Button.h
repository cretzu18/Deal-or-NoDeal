#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Button {
    sf::RectangleShape button;
    sf::Text buttonText;
    sf::Font font;

public:
    explicit Button(const std::string& text = "", float posX = 0, float posY = 0, float width = 100, float height = 100);
    Button(const Button& other);
    Button& operator=(const Button& other);
    ~Button() = default;

    friend std::ostream& operator<<(std::ostream& os, const Button& button);
    void draw(sf::RenderWindow& window) const;
    bool isMouseOver(const sf::RenderWindow& window) const;
    bool isClicked(const sf::RenderWindow& window) const;
};

#endif // BUTTON_HPP
