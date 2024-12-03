#ifndef VOLUMESLIDER_H
#define VOLUMESLIDER_H

#include <SFML/Graphics.hpp>

/**
 * @class VolumeSlider
 * @brief A class that represents a volume slider for adjusting the volume level.
 *
 * The `VolumeSlider` class is used to create and manage a slider component that allows the user to adjust a value between a minimum and maximum range, in this case, controlling the volume level. The slider consists of a track (represented as a rectangle) and a knob that the user can drag horizontally to adjust the volume level. The class provides methods to draw the slider on the screen and update the position of the knob based on user input.
 *
 * The volume level is expressed as a float value between 0 and 100, and the position of the knob on the slider represents this value.
 *
 * @see SFML for window and graphics handling.
 */
class VolumeSlider {
    sf::RectangleShape volumeSlider; ///< The rectangle representing the volume slider.
    sf::RectangleShape volumeKnob; ///< The knob that can be moved to adjust volume.
    float volumeLevel; ///< The current volume level represented as a float.

public:
    /**
     * @brief Constructs a VolumeSlider at the specified position.
     *
     * This constructor initializes the volume slider with a knob at the given position.
     * It sets the initial volume level to 0.5 (50%).
     *
     * @param x The X-coordinate of the slider.
     * @param y The Y-coordinate of the slider.
     */
    VolumeSlider(float x, float y);

    /**
     * @brief Destructor for the VolumeSlider.
     */
    ~VolumeSlider() = default;

    /**
     * @brief Gets the current volume level.
     *
     * This method returns the current volume level as a float, where 0.0 represents no volume,
     * and 1.0 represents maximum volume.
     *
     * @return The current volume level.
     */
    [[nodiscard]] float getVolumeLevel() const { return volumeLevel; }

    /**
     * @brief Draws the volume slider and knob onto the window.
     *
     * This method renders the slider and its knob to the specified window.
     *
     * @param window The render window where the volume slider is drawn.
     */
    void draw(sf::RenderWindow &window) const;

    /**
     * @brief Updates the volume slider based on user interaction.
     *
     * This method checks for user input, such as dragging the knob or clicking on the slider,
     * and updates the volume level accordingly.
     *
     * @param window The render window where the event is being processed.
     * @param event The event to be processed, which may include user input on the slider.
     */
    void update(const sf::RenderWindow& window, const sf::Event& event);
};

#endif
