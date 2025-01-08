#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
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


class Command {
public:
	virtual ~Command() = default;
	virtual void execute(sf::RenderWindow& window, GameState& gameState, int& round) = 0;
};

class PlayCommand final : public Command {
public:
	void execute(sf::RenderWindow& window, GameState& gameState, int& round) override {
		window.clear();
		gameState = CASES;
		round = 1;
	}
};

class ExitCommand final : public Command {
public:
	void execute(sf::RenderWindow& window, GameState& gameState, int& round) override {
		window.close();
		gameState = MENU;
		round = 0;
	}
};

class SettingsCommand final : public Command {
public:
	void execute(sf::RenderWindow& window, GameState& gameState, int& round) override {
		window.clear();
		gameState = SETTINGS;
		round = 0;
	}
};

class BackCommand final : public Command {
public:
	void execute(sf::RenderWindow& window, GameState& gameState, int& round) override {
		window.clear();
		gameState = MENU;
		round = 0;
	}
};


/**
 * @brief Abstract base class representing a generic button in the game.
 */
class Button {
	sf::RectangleShape button;  ///< Rectangle shape representing the button's appearance.
	sf::Text buttonText;        ///< Text displayed on the button.
	sf::Font font;              ///< Font used for the button's text.
	std::shared_ptr<Command> command;

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
	 * @brief Destructor for the Button class.
	 */
	~Button() = default;

	/**
	 * @brief Stream insertion operator for displaying button details.
	 *
	 * @param os The output stream.
	 * @param button The Button object.
	 * @return A reference to the output stream.
	 */
	friend std::ostream& operator<<(std::ostream& os, const Button& button);

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

	void setCommand(std::shared_ptr<Command> cmd) {
		command = std::move(cmd);
	}

	const std::shared_ptr<Command>& getCommand() const {
		return command;
	}

	void action(sf::RenderWindow& window, GameState& gameState, int& round) const {
		if (command)
			command->execute(window, gameState, round);
	}
};


#endif // BUTTON_HPP
