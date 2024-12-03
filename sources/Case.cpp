#include "../headers/Case.h"

/**
 * @brief Constructs a Case object with an optional initial amount of money.
 *
 * This constructor initializes the Case object with a specified amount of money and loads the associated
 * texture and font. The texture is applied to the sprite, and the amount is displayed as text on the sprite.
 *
 * @param money The amount of money in the case. Defaults to 0.
 * @throws TextureError If the texture file could not be loaded.
 * @throws FontError If the font file could not be loaded.
 */
Case::Case(const double money) : amount(money), selected(false) {
	if (!texture.loadFromFile("../resources/case.png"))
		throw TextureError("The case texture could not be loaded!");

	sprite.setTexture(texture);
	sprite.scale(static_cast<float>(0.35), static_cast<float>(0.35));

	if (!font.loadFromFile("../resources/arial.ttf"))
		throw FontError("The font could not be loaded!");

	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Black);
	text.setString("$" + std::to_string(static_cast<int>(amount)));
}

/**
 * @brief Copy constructor for the Case class.
 *
 * This constructor creates a copy of the provided Case object, including its amount, selected state,
 * sprite, texture, and text properties.
 *
 * @param other The Case object to copy.
 */
Case::Case(const Case &other): amount(other.amount), selected(other.selected), sprite(other.sprite), texture(other.texture), text(other.text), font(other.font) {
	sprite.setTexture(texture);
	text.setFont(font);
}

/**
 * @brief Assigns one Case object to another.
 *
 * This operator allows for assigning the properties of one Case to another, ensuring that the amount,
 * selection state, sprite, texture, and text are copied properly.
 *
 * @param other The Case object to copy from.
 * @return A reference to the current Case object.
 */
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

/**
 * @brief Outputs the amount of money in the case to the output stream.
 *
 * This operator writes the amount of money in the case to the provided output stream.
 *
 * @param os The output stream to write to.
 * @param c The Case object to output.
 * @return The output stream with the case's amount information.
 */
std::ostream &operator<<(std::ostream &os, const Case &c) {
	os << "The case has " << c.amount << "$.\n";
	return os;
}

/**
 * @brief Marks the case as selected.
 *
 * This function sets the case's selected state to true and changes the sprite's color to green.
 * The position of the amount text is also updated to be centered on the case sprite.
 */
void Case::selectCase() {
	selected = true;
	sprite.setColor(sf::Color::Green);

	this->setPositionText();
}

/**
 * @brief Marks the case as deselected.
 *
 * This function sets the case's selected state to false and changes the sprite's color to white.
 */
void Case::deselectCase() {
	selected = false;
	sprite.setColor(sf::Color::White);
}

/**
 * @brief Checks if the case is selected.
 *
 * This function checks if the case has been selected by the player, indicated by the sprite's color being green.
 *
 * @return True if the case is selected, otherwise false.
 */
bool Case::isSelected() const {
	return (sprite.getColor() == sf::Color::Green);
}

/**
 * @brief Eliminates the case, making it unavailable in the game.
 *
 * This function marks the case as eliminated by changing the sprite's color to red and updating the text position.
 */
void Case::eliminateCase() {
	selected = true;
	sprite.setColor(sf::Color::Red);

	this->setPositionText();
}

/**
 * @brief Checks if the case is eliminated.
 *
 * This function checks if the case has been eliminated, indicated by the sprite's color being red.
 *
 * @return True if the case is eliminated, otherwise false.
 */
bool Case::isEliminated() const {
	return (sprite.getColor() == sf::Color::Red);
}


/**
 * @brief Draws the Case object to the specified window.
 *
 * This function draws the case sprite and, if the case is eliminated, also draws the amount text on top of the sprite.
 *
 * @param window The SFML render window where the case should be drawn.
 */
void Case::draw(sf::RenderWindow &window) const {
	window.draw(sprite);
	if (sprite.getColor() == sf::Color::Red)
		window.draw(text);
}

/**
 * @brief Sets the position of the case sprite.
 *
 * This function sets the position of the case sprite on the screen.
 *
 * @param x The x-coordinate of the case's position.
 * @param y The y-coordinate of the case's position.
 */
void Case::setPosition(const float x, const float y) {
	sprite.setPosition(x, y);
}

/**
 * @brief Centers the amount text on the case sprite.
 *
 * This function adjusts the position of the amount text so that it is centered within the bounds of the case sprite.
 */
void Case::setPositionText() {
	const sf::FloatRect bounds = text.getLocalBounds();
	const sf::Vector2f spritePosition = sprite.getPosition();
	const sf::Vector2f spriteSize(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
	text.setPosition(spritePosition.x + spriteSize.x / 2 - bounds.width / 2, spritePosition.y + spriteSize.y / 2 - bounds.height / 2);
}

/**
 * @brief Checks if the mouse is hovering over the case.
 *
 * This function checks if the mouse pointer is currently over the case sprite and if the case is not selected.
 *
 * @param window The SFML render window to get the mouse position.
 * @return True if the mouse is over the case and it is not selected, otherwise false.
 */
bool Case::isMouseOver(const sf::RenderWindow& window) const {
	if (selected) return false;
	const sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	return sprite.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

/**
 * @brief Checks if the case is clicked.
 *
 * This function checks whether the mouse is hovering over the case and whether the left mouse button is pressed.
 *
 * @param window The SFML render window to get the mouse position and button state.
 * @return True if the case is clicked, otherwise false.
 */

bool Case::isClicked(const sf::RenderWindow& window) const {
	return isMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

/**
 * @brief Gets the amount of money in the case.
 *
 * This function returns the amount of money contained in the case.
 *
 * @return The amount of money in the case.
 */
double Case::getAmount() const {
	return amount;
}
