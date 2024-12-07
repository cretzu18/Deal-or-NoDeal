#ifndef CASE_HPP
#define CASE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Errors.h"

/**
 * @brief Represents a case in the Deal or No Deal game.
 *
 * A Case object contains an amount of money, a sprite for display, and text representing the amount.
 * The case can be selected, deselected, or eliminated, and has a visual representation in the game window.
 */
class Case {
private:
    double amount; ///< The amount of money contained in the case.
    bool selected; ///< A flag indicating if the case has been selected by the player.
    sf::Sprite sprite; ///< The sprite representing the case visually.
    sf::Texture texture; ///< The texture for the sprite of the case.
    sf::Text text; ///< The text displaying the amount of money on the case.
    sf::Font font; ///< The font used for the text.

public:
    /**
     * @brief Constructs a Case object with an optional initial amount.
     *
     * This constructor initializes a case with a specific amount of money. If no amount is provided,
     * the default value of 0 is used.
     *
     * @param money The amount of money in the case. Defaults to 0.
     */
    explicit Case(double money = 0);

    /**
     * @brief Copy constructor for the Case class.
     *
     * Initializes a new Case as a copy of the given Case object.
     *
     * @param other The Case object to copy from.
     */
    Case(const Case &other);

    /**
     * @brief Assigns one Case object to another.
     *
     * This operator allows for assigning the properties of one Case to another, ensuring that the amount,
     * selection state, sprite, texture, and text are copied properly.
     *
     * @param other The Case object to copy from.
     * @return A reference to the current Case object.
     */
    Case& operator=(const Case &other);

    /// Destructor for the Case class.
    ~Case() = default;

    /**
     * @brief Outputs a description of the Case object to the output stream.
     *
     * This operator outputs the amount of money in the case to the given output stream.
     *
     * @param os The output stream to write to.
     * @param c The Case object to output.
     * @return The output stream with the added description.
     */
    friend std::ostream &operator<<(std::ostream &os, const Case &c);

    /**
     * @brief Marks the case as selected.
     *
     * This function sets the case's selected state to true.
     */
    void selectCase();

    /**
     * @brief Marks the case as deselected.
     *
     * This function sets the case's selected state to false.
     */
    void deselectCase();

    /**
     * @brief Checks if the case is selected.
     *
     * This function returns true if the case is selected, otherwise false.
     *
     * @return True if the case is selected, otherwise false.
     */
    bool isSelected() const;

    /**
     * @brief Eliminates the case, making it unavailable in the game.
     *
     * This function marks the case as eliminated.
     */
    void eliminateCase();

    /**
     * @brief Checks if the case is eliminated.
     *
     * This function returns true if the case has been eliminated, otherwise false.
     *
     * @return True if the case is eliminated, otherwise false.
     */
    bool isEliminated() const;

    /**
     * @brief Sets the position of the amount text relative to the case sprite.
     *
     * This function ensures that the amount text is centered on the case sprite.
     */
    void setPositionText();

    /**
     * @brief Draws the Case object to the specified window.
     *
     * This function draws both the case sprite and the amount text to the render window.
     *
     * @param window The SFML render window to draw the case on.
     */
    void draw(sf::RenderWindow &window) const ;

    /**
    * @brief Draws the amount associated with this `Case` object to the screen.
    *
    * @param window A reference to the `sf::RenderWindow` object used to render the game.
    * @param x The x-coordinate where the amount text will be positioned.
    * @param y The y-coordinate where the amount text will be positioned.
    */
    void drawAmount(sf::RenderWindow &window, float x, float y) const;

    /**
     * @brief Sets the position of the case.
     *
     * This function sets the position of the case sprite on the screen.
     *
     * @param x The x-coordinate of the case's position.
     * @param y The y-coordinate of the case's position.
     */
    void setPosition(float x, float y);

    /**
     * @brief Checks if the mouse cursor is hovering over the case.
     *
     * This function checks whether the mouse pointer is currently over the case's area.
     *
     * @param window The SFML render window used to get the mouse position.
     * @return True if the mouse is over the case, otherwise false.
     */
    bool isMouseOver(const sf::RenderWindow& window) const;

    /**
     * @brief Checks if the case is clicked.
     *
     * This function checks whether the mouse pointer is over the case and if the left mouse button is pressed.
     *
     * @param window The SFML render window used to get the mouse position and button state.
     * @return True if the mouse is over the case and clicked, otherwise false.
     */
    bool isClicked(const sf::RenderWindow& window) const;

    /**
     * @brief Returns the amount of money in the case.
     *
     * This function retrieves the amount of money contained in the case.
     *
     * @return The amount of money in the case.
     */
    [[nodiscard]] double getAmount() const;
};

#endif // CASE_HPP
