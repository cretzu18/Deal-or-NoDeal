#include "../headers/Case.h"

Case::Case(const double money) : amount(money), selected(false) {
    if (!texture.loadFromFile("../resources/case.png")) {
        std::cout << "Failed to load case" << std::endl;
        exit(1);
    }
    sprite.setTexture(texture);
    sprite.scale(static_cast<float>(0.3), static_cast<float>(0.3));
}

Case::Case(const Case &other): amount(other.amount), selected(other.selected), sprite(other.sprite), texture(other.texture) {
    sprite.setTexture(other.texture);
}

Case& Case::operator=(const Case &other) {
    if (this != &other) {
        amount = other.amount;
        selected = other.selected;
        sprite = other.sprite;
        texture = other.texture;
        sprite.setTexture(texture);
    }
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Case &c) {
    os << "The case has " << c.amount << "$.\n";
    return os;
}

void Case::selectCase() {
    selected = true;
    sprite.setColor(sf::Color::Red);
}

void Case::draw(sf::RenderWindow &window) const {
    window.draw(sprite);
}

void Case::setPosition(const float x, const float y) {
    sprite.setPosition(x, y);
}

bool Case::isMouseOver(const sf::RenderWindow& window) const {
    if (selected) return false;
    const sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return sprite.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

bool Case::isClicked(const sf::RenderWindow& window) const {
    return isMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}
