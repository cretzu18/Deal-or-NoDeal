#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Errors.h"

/**
 * @enum GameState
 * @brief Enum representing the different states of the game.
 */
enum GameState {
	MENU,        ///< The game is in the menu state
	SETTINGS,    ///< The game is in the settings state
	CASES,       ///< The game is in the case selection state
	GAME_OVER    ///< The game is in the game over state
};

/**
 * @brief Abstract base class representing a generic button in the game.
 */
class Button {
	sf::RectangleShape button;  ///< Rectangle shape representing the button's appearance.
	sf::Text buttonText;        ///< Text displayed on the button.
	sf::Font font;              ///< Font used for the button's text.

public:
	/**
	 * @brief Constructor to initialize a Button with text, position, and size.
	 *
	 * @param text The text displayed on the button.
	 * @param posX X-coordinate of the button's position.
	 * @param posY Y-coordinate of the button's position.
	 * @param width Width of the button.
	 * @param height Height of the button.
	 */
	explicit Button(const std::string& text = "", float posX = 0, float posY = 0, float width = 100, float height = 100);

	/**
	 * @brief Copy constructor for the Button class.
	 *
	 * @param other The Button object to copy.
	 */
	Button(const Button& other);

	/**
	 * @brief Copy assignment operator for the Button class.
	 *
	 * @param other The Button object to assign.
	 * @return A reference to the current Button object.
	 */
	Button& operator=(const Button& other);

	/**
	 * @brief Virtual destructor for the Button class.
	 */
	virtual ~Button() = default;

	/**
	 * @brief Stream insertion operator for displaying button details.
	 *
	 * @param os The output stream.
	 * @param button The Button object.
	 * @return A reference to the output stream.
	 */
	friend std::ostream& operator<<(std::ostream& os, const Button& button);

	/**
	 * @brief Pure virtual method defining the button's action when clicked.
	 *
	 * @param window The SFML render window.
	 * @param gameState The current game state to be modified.
	 * @param round The current game round to be modified.
	 */
	virtual void action(sf::RenderWindow& window, GameState& gameState, int& round) = 0;

	/**
	 * @brief Draws the button on the given SFML render window.
	 *
	 * @param window The SFML render window.
	 */
	void draw(sf::RenderWindow& window) const;

	/**
	 * @brief Checks if the mouse is hovering over the button.
	 *
	 * @param window The SFML render window.
	 * @return True if the mouse is over the button, otherwise false.
	 */
	bool isMouseOver(const sf::RenderWindow& window) const;

	/**
	 * @brief Checks if the button has been clicked.
	 *
	 * @param window The SFML render window.
	 * @return True if the button is clicked, otherwise false.
	 */
	bool isClicked(const sf::RenderWindow& window) const;

	/**
	 * @brief Pure virtual method for cloning the button.
	 *
	 * Used for creating a copy of the button dynamically.
	 *
	 * @return A pointer to the cloned Button object.
	 */
	virtual Button* clone() = 0;
};

/**
 * @brief A Button to start the game.
 */
class PlayButton final : public Button {
public:
	/**
	 * @brief Constructor to initialize the PlayButton.
	 *
	 * @param text The text displayed on the button (default: "Play").
	 * @param posX X-coordinate of the button's position.
	 * @param posY Y-coordinate of the button's position.
	 * @param width Width of the button.
	 * @param height Height of the button.
	 */
	explicit PlayButton(const std::string& text = "Play", const float posX = 0, const float posY = 0, const float width = 100, const float height = 100)
		: Button(text, posX, posY, width, height) {};

	/**
	 * @brief Creates a copy of the PlayButton.
	 *
	 * @return A pointer to the cloned PlayButton object.
	 */
	[[maybe_unused]] PlayButton* clone() override {
		return new PlayButton(*this);
	}

	/**
	 * @brief Action performed when the PlayButton is clicked.
	 *
	 * Sets the game state to CASES and initializes the first round.
	 *
	 * @param window The SFML render window.
	 * @param gameState The current game state to be modified.
	 * @param round The current game round to be modified.
	 */
	void action(sf::RenderWindow& window, GameState& gameState, int& round) override {
		window.clear();
		gameState = CASES;
		round = 1;
	}
};

/**
 * @brief A Button to exit the game.
 */
class ExitButton final : public Button {
public:
	/**
	 * @brief Constructor to initialize the ExitButton.
	 *
	 * @param text The text displayed on the button (default: "Exit").
	 * @param posX X-coordinate of the button's position.
	 * @param posY Y-coordinate of the button's position.
	 * @param width Width of the button.
	 * @param height Height of the button.
	 */
	explicit ExitButton(const std::string& text = "Exit", const float posX = 0, const float posY = 0, const float width = 100, const float height = 100)
		: Button(text, posX, posY, width, height) {};

	/**
	 * @brief Creates a copy of the ExitButton.
	 *
	 * @return A pointer to the cloned ExitButton object.
	 */
	[[maybe_unused]] ExitButton* clone() override {
		return new ExitButton(*this);
	}

	/**
	 * @brief Action performed when the ExitButton is clicked.
	 *
	 * Closes the game window and sets the game state to MENU.
	 *
	 * @param window The SFML render window.
	 * @param gameState The current game state to be modified.
	 * @param round The current game round to be reset.
	 */
	void action (sf::RenderWindow& window, GameState& gameState, int& round) override {
		window.close();
		gameState = MENU;
		round = 0;
	}
};

/**
 * @brief A Button to open the settings menu.
 */
class SettingsButton final : public Button {
public:
	/**
	 * @brief Constructor to initialize the SettingsButton.
	 *
	 * @param text The text displayed on the button (default: "Settings").
	 * @param posX X-coordinate of the button's position.
	 * @param posY Y-coordinate of the button's position.
	 * @param width Width of the button.
	 * @param height Height of the button.
	 */
	explicit SettingsButton(const std::string& text = "Settings", const float posX = 0, const float posY = 0, const float width = 100, const float height = 100)
		: Button(text, posX, posY, width, height) {};

	/**
	 * @brief Creates a copy of the SettingsButton.
	 *
	 * @return A pointer to the cloned SettingsButton object.
	 */
	[[maybe_unused]] SettingsButton* clone() override {
		return new SettingsButton(*this);
	}

	/**
	 * @brief Action performed when the SettingsButton is clicked.
	 *
	 * Sets the game state to SETTINGS.
	 *
	 * @param window The SFML render window.
	 * @param gameState The current game state to be modified.
	 * @param round The current game round to be reset.
	 */
	void action(sf::RenderWindow& window, GameState& gameState, int& round) override {
		window.clear();
		gameState = SETTINGS;
		round = 0;
	}
};

/**
 * @brief A Button to return to the main menu.
 */
class BackButton final : public Button {
public:
	/**
	 * @brief Constructor to initialize the BackButton.
	 *
	 * @param text The text displayed on the button (default: "Back").
	 * @param posX X-coordinate of the button's position.
	 * @param posY Y-coordinate of the button's position.
	 * @param width Width of the button.
	 * @param height Height of the button.
	 */
	explicit BackButton(const std::string& text = "Back", const float posX = 0, const float posY = 0, const float width = 100, const float height = 100)
		: Button(text, posX, posY, width, height) {};

	/**
	 * @brief Creates a copy of the BackButton.
	 *
	 * @return A pointer to the cloned BackButton object.
	 */
	[[maybe_unused]] BackButton* clone() override {
		return new BackButton(*this);
	}

	/**
	 * @brief Action performed when the BackButton is clicked.
	 *
	 * Sets the game state to MENU.
	 *
	 * @param window The SFML render window.
	 * @param gameState The current game state to be modified.
	 * @param round The current game round to be reset.
	 */
	void action(sf::RenderWindow& window, GameState& gameState, int& round) override {
		window.clear();
		gameState = MENU;
		round = 0;
	}
};

#endif // BUTTON_HPP
