#include "../headers/Button.h"

/**
 * @brief Constructs a Button with the specified text, position, size, and appearance.
 *
 * This constructor initializes the button with a specified text label, position, size, and font.
 * It also sets the button's color and outlines.
 *
 * @param text The text to display on the button.
 * @param posX The x-coordinate of the button's position.
 * @param posY The y-coordinate of the button's position.
 * @param width The width of the button.
 * @param height The height of the button.
 * @throws FontError If the font file could not be loaded.
 */
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

/**
 * @brief Copy constructor for the Button class.
 *
 * Initializes a new Button as a copy of the given Button object.
 *
 * @param other The Button object to copy.
 */
Button::Button(const Button& other) : button(other.button), buttonText(other.buttonText), font(other.font) {
    buttonText.setFont(font);
}

/**
 * @brief Assigns one Button object to another.
 *
 * This operator allows for assigning the properties of one Button to another,
 * ensuring deep copies of the button and buttonText objects.
 *
 * @param other The Button object to copy from.
 * @return A reference to the current Button object.
 */
Button& Button::operator=(const Button& other) {
    if (this != &other) {
        button = other.button;
        buttonText = other.buttonText;
        font = other.font;
        buttonText.setFont(font);
    }
    return *this;
}


/**
 * @brief Outputs a description of the Button object to the output stream.
 *
 * This operator outputs a string indicating which button was pressed,
 * using the button's label as part of the message.
 *
 * @param os The output stream to write to.
 * @param button The Button object to output.
 * @return The output stream with the added description.
 */
std::ostream& operator<<(std::ostream& os, const Button& button) {
    os << "You pressed the " << button.buttonText.getString().toAnsiString() << " button.\n";
    return os;
}

/**
 * @brief Draws the Button to the specified window.
 *
 * This function draws both the button shape and the text to the given render window.
 *
 * @param window The SFML render window to draw the button on.
 */
void Button::draw(sf::RenderWindow& window) const {
    window.draw(button);
    window.draw(buttonText);
}

/**
 * @brief Checks if the mouse cursor is hovering over the button.
 *
 * This function checks whether the mouse pointer is currently over the button's area.
 *
 * @param window The SFML render window used to get the mouse position.
 * @return True if the mouse is over the button, otherwise false.
 */
bool Button::isMouseOver(const sf::RenderWindow& window) const {
    const sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return button.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

/**
 * @brief Checks if the button is clicked.
 *
 * This function checks whether the mouse pointer is over the button and if the left mouse button is pressed.
 *
 * @param window The SFML render window used to get the mouse position and button state.
 * @return True if the mouse is over the button and clicked, otherwise false.
 */
bool Button::isClicked(const sf::RenderWindow& window) const {
    return isMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}
