#include "../headers/Settings.h"

Settings::Settings()
	: backButton (std::make_shared<ExitButton>("BACK", 50, 50, 300, 100))
	, menuSlider(VolumeSlider(100, 200))
	, gameSlider(VolumeSlider(100, 300))
{
}

/**
 * @brief Draws the settings screen including the volume sliders and text.
 *
 * This method renders the back button, the menu and game volume sliders,
 * and the corresponding text labels for the volume settings onto the window.
 *
 * @param window The render window where the settings are drawn.
 * @throws FontError If the font could not be loaded.
 */
void Settings::draw(sf::RenderWindow& window) const {
	backButton->draw(window);
	menuSlider.draw(window);
	gameSlider.draw(window);

	sf::Font font;
	if (!font.loadFromFile("../resources/OakleyRidge.ttf"))
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

/**
 * @brief Updates the settings based on user input.
 *
 * This method checks for events in the settings screen, such as the back button click
 * and the adjustments made to the menu and game volume sliders. If the back button is clicked,
 * it changes the game state to MENU.
 *
 * @param window The render window where the settings are updated.
 * @param event The event to be processed for the settings screen.
 * @param gameState The current game state, which can be updated to MENU if the back button is clicked.
 */
void Settings::update(const sf::RenderWindow& window, const sf::Event& event, GameState& gameState) {
	if (backButton->isClicked(window)) {
		gameState = MENU;
		return;
	}

	menuSlider.update(window, event);
	gameSlider.update(window, event);
}