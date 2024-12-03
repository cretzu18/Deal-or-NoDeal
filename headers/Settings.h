#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"
#include "VolumeSlider.h"
#include "Errors.h"
#include <memory>


/**
 * @class Settings
 * @brief Handles the game settings such as volume levels and provides a menu interface.
 *
 * The `Settings` class allows the user to adjust game settings such as menu and game volume levels.
 * It provides methods to draw the settings menu, update the settings based on user input, and access the
 * volume levels for the menu and the game.
 */
class Settings {
  std::shared_ptr<Button> backButton; ///< Button to go back to the main menu
  VolumeSlider menuSlider; ///< Slider to adjust the menu volume
  VolumeSlider gameSlider; ///< Slider to adjust the game volume

public:
  /**
   * @brief Constructs a Settings object and initializes the sliders and back button.
   *
   * The constructor sets up the back button and volume sliders for both the menu and the game.
   */
  Settings();

  /**
   * @brief Destructor for the Settings class.
   *
   * Cleans up any resources used by the `Settings` class (e.g., buttons, sliders).
   */
  ~Settings() = default;

  /**
   * @brief Gets the current menu volume level.
   *
   * This method retrieves the current volume level of the menu as set by the user.
   *
   * @return The current volume level of the menu.
   */
  [[nodiscard]] float getMenuVolumeLevel() const { return menuSlider.getVolumeLevel(); }

  /**
   * @brief Gets the current game volume level.
   *
   * This method retrieves the current volume level of the game as set by the user.
   *
   * @return The current volume level of the game.
   */
  [[nodiscard]] float getGameVolumeLevel() const { return gameSlider.getVolumeLevel(); }

  /**
   * @brief Draws the settings menu to the window.
   *
   * This method renders the settings menu, including the sliders and the back button, to the given
   * window. It updates the window display to show the settings interface.
   *
   * @param window The window to draw the settings menu on.
   */
  void draw(sf::RenderWindow& window) const;

  /**
   * @brief Updates the settings menu based on user input and changes the game state.
   *
   * This method handles user interactions with the settings menu. It listens for input events,
   * such as slider adjustments or button clicks, and updates the game state accordingly.
   *
   * @param window The window that receives the input events.
   * @param event The event that occurred (e.g., button click or slider change).
   * @param gameState The current state of the game, which may be modified by the settings.
   */
  void update(const sf::RenderWindow& window, const sf::Event& event, GameState& gameState);
};

#endif //SETTINGS_H
