#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Errors.h"

enum GameState {
	MENU,
	SETTINGS,
	CASES,
	GAME_OVER
};

class Button {
	sf::RectangleShape button;
	sf::Text buttonText;
	sf::Font font;

public:
	explicit Button(const std::string& text = "", float posX = 0, float posY = 0, float width = 100, float height = 100);
	Button(const Button& other);
	Button& operator=(const Button& other);
	virtual ~Button() = default;

	friend std::ostream& operator<<(std::ostream& os, const Button& button);
	virtual void action(sf::RenderWindow& window, GameState& gameState, int& round) = 0;
	void draw(sf::RenderWindow& window) const;
	bool isMouseOver(const sf::RenderWindow& window) const;
	bool isClicked(const sf::RenderWindow& window) const;
	virtual Button* clone() = 0;
};


class PlayButton final : public Button {
public:
	explicit PlayButton(const std::string& text = "Play", const float posX = 0, const float posY = 0, const float width = 100, const float height = 100)
		: Button(text, posX, posY, width, height) {};

	[[maybe_unused]] PlayButton* clone() override {
		return new PlayButton(*this);
	}
	void action(sf::RenderWindow& window, GameState& gameState, int& round) override {
		window.clear();
		gameState = CASES;
		round = 1;
	}
};

class ExitButton final : public Button {
public:
	explicit ExitButton(const std::string& text = "Exit", const float posX = 0, const float posY = 0, const float width = 100, const float height = 100)
		: Button(text, posX, posY, width, height) {};

	[[maybe_unused]] ExitButton* clone() override {
		return new ExitButton(*this);
	}
	void action (sf::RenderWindow& window, GameState& gameState, int& round) override {
		window.close();
		gameState = MENU;
		round = 0;
	}
};

class SettingsButton final : public Button {
public:
	explicit SettingsButton(const std::string& text = "Settings", const float posX = 0, const float posY = 0, const float width = 100, const float height = 100)
		: Button(text, posX, posY, width, height) {};

	[[maybe_unused]] SettingsButton* clone() override {
		return new SettingsButton(*this);
	}
	void action(sf::RenderWindow& window, GameState& gameState, int& round) override {
		window.clear();
		gameState = SETTINGS;
		round = 0;
	}
};

class BackButton final : public Button {
public:
	explicit BackButton(const std::string& text = "Back", const float posX = 0, const float posY = 0, const float width = 100, const float height = 100)
		: Button(text, posX, posY, width, height) {};

	[[maybe_unused]] BackButton* clone() override {
		return new BackButton(*this);
	}
	void action(sf::RenderWindow& window, GameState& gameState, int& round) override {
		window.clear();
		gameState = MENU;
		round = 0;
	}
};

#endif // BUTTON_HPP
