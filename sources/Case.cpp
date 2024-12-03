#include "../headers/Case.h"

Case::Case(const double money) : amount(money), selected(false) {
    if (!texture.loadFromFile("../resources/case.png")) {
        std::cout << "Failed to load case" << std::endl;
        exit(1);
    }
    sprite.setTexture(texture);
    sprite.scale(static_cast<float>(0.35), static_cast<float>(0.35));

    if (!font.loadFromFile("../resources/arial.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        exit(1);
    }

    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setString("$" + std::to_string(static_cast<int>(amount)));
}

Case::Case(const Case &other): amount(other.amount), selected(other.selected), sprite(other.sprite), texture(other.texture), text(other.text), font(other.font) {
    sprite.setTexture(texture);
    text.setFont(font);
}

Case& Case::operator=(const Case &other) {
    if (this != &other) {
        amount = other.amount;
        selected = other.selected;
        sprite = other.sprite;
        texture = other.texture;
        text = other.text;
        font = other.font;
        sprite.setTexture(texture);
        text.setFont(font);
    }
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Case &c) {
    os << "The case has " << c.amount << "$.\n";
    return os;
}

void Case::selectCase() {
    selected = true;
    sprite.setColor(sf::Color::Green);

    this->setPositionText();
}

void Case::deselectCase() {
    selected = false;
    sprite.setColor(sf::Color::White);
}

bool Case::isSelected() const {
    return (sprite.getColor() == sf::Color::Green);
}

void Case::eliminateCase(sf::RenderWindow &window) {
    selected = true;
    sprite.setColor(sf::Color::Red);

    this->setPositionText();
}

bool Case::isEliminated() const {
    return (sprite.getColor() == sf::Color::Red);
}

void Case::draw(sf::RenderWindow &window) const {
    window.draw(sprite);
    if (sprite.getColor() == sf::Color::Red)
        window.draw(text);
}

void Case::setPosition(const float x, const float y) {
    sprite.setPosition(x, y);
}

void Case::setPositionText() {
    const sf::FloatRect bounds = text.getLocalBounds();
    const sf::Vector2f spritePosition = sprite.getPosition();
    const sf::Vector2f spriteSize(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
    text.setPosition(spritePosition.x + spriteSize.x / 2 - bounds.width / 2, spritePosition.y + spriteSize.y / 2 - bounds.height / 2);
}

bool Case::isMouseOver(const sf::RenderWindow& window) const {
    if (selected) return false;
    const sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return sprite.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

bool Case::isClicked(const sf::RenderWindow& window) const {
    return isMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

double Case::getAmount() const {
    return amount;
}

