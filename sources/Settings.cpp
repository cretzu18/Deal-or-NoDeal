#include "../headers/Settings.h"

Settings::Settings()
	: backButton (std::make_shared<ExitButton>("BACK", 50, 50, 300, 100))
	, menuSlider(VolumeSlider(100, 200))
	, gameSlider(VolumeSlider(100, 300))
{
}

void Settings::draw(sf::RenderWindow& window) const {
	backButton->draw(window);
	menuSlider.draw(window);
	gameSlider.draw(window);

	sf::Font font;
	if (!font.loadFromFile("./arial.ttf"))
		throw FontError("The font could not be loaded!");

	sf::Text menuText;
	menuText.setFont(font);
	menuText.setString("Menu music volume");
	menuText.setCharacterSize(40);
	menuText.setFillColor(sf::Color::Black);
	menuText.setStyle(sf::Text::Bold);

	sf::Text gameText;
	gameText.setFont(font);
	gameText.setString("Game music volume");
	gameText.setCharacterSize(40);
	gameText.setFillColor(sf::Color::Black);
	gameText.setStyle(sf::Text::Bold);

	menuText.setPosition(150, 200);
	gameText.setPosition(150, 300);

	window.draw(menuText);
	window.draw(gameText);
}

void Settings::update(const sf::RenderWindow& window, const sf::Event& event, GameState& gameState) {
	if (backButton->isClicked(window)) {
		gameState = MENU;
		return;
	}

	menuSlider.update(window, event);
	gameSlider.update(window, event);
}