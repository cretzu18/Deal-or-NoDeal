#include "../headers/Settings.h"

Settings::Settings(): menuSlider(VolumeSlider(100, 200)), gameSlider(VolumeSlider(100, 300)) {
  backButton = std::make_shared<ExitButton>("Back", 50, 50, 300, 100);
}

void Settings::draw(sf::RenderWindow& window) {
  backButton->draw(window);
  menuSlider.draw(window);
  gameSlider.draw(window);

  sf::Font font;
  if (!font.loadFromFile("../resources/OakleyRidge.ttf")) {
    std::cerr << "Failed to load font." << std::endl;
    exit(1);
  }

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