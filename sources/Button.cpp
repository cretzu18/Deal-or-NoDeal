#include "../headers/Button.h"

Button::Button(const std::string& text, const float posX, const float posY, const float width, const float height) {
    if (!font.loadFromFile("../resources/OakleyRidge.ttf"))
        throw FontError("The font could not be loaded!");

    button.setSize(sf::Vector2f(width, height));
    button.setPosition(posX, posY);
    button.setFillColor(sf::Color(255, 255, 102));
    button.setOutlineColor(sf::Color::Black);
    button.setOutlineThickness(1);
    button.setPosition(posX, posY);

    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(30);
    buttonText.setFillColor(sf::Color::Black);
    const sf::FloatRect textBounds = buttonText.getGlobalBounds();
    buttonText.setPosition(posX + width / 2 - textBounds.width / 2,
                           posY + height / 2 - textBounds.height / 2);
}

Button::Button(const Button& other) : button(other.button), buttonText(other.buttonText), font(other.font) {
    buttonText.setFont(font);
}

Button& Button::operator=(const Button& other) {
    if (this != &other) {
        button = other.button;
        buttonText = other.buttonText;
        font = other.font;
        buttonText.setFont(font);
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Button& button) {
    os << "You pressed the " << button.buttonText.getString().toAnsiString() << " button.\n";
    return os;
}

void Button::draw(sf::RenderWindow& window) const {
    window.draw(button);
    window.draw(buttonText);
}

bool Button::isMouseOver(const sf::RenderWindow& window) const {
    const sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return button.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

bool Button::isClicked(const sf::RenderWindow& window) const {
    return isMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}
