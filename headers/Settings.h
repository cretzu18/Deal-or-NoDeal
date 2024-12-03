#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"
#include "VolumeSlider.h"
#include "Errors.h"
#include <memory>


class Settings {
  std::shared_ptr<Button> backButton;
  VolumeSlider menuSlider;
  VolumeSlider gameSlider;

public:
  Settings();
  ~Settings() = default;
  [[nodiscard]] float getMenuVolumeLevel() const { return menuSlider.getVolumeLevel(); }
  [[nodiscard]] float getGameVolumeLevel() const { return gameSlider.getVolumeLevel(); }
  void draw(sf::RenderWindow& window);
  void update(const sf::RenderWindow& window, const sf::Event& event, GameState& gameState);
};

#endif //SETTINGS_H
