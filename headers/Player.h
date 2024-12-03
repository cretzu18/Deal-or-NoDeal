#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <iostream>
#include "Case.h"

/**
 * @class Player
 * @brief Represents a player in the game, including their username and the selected case.
 *
 * The Player class manages the player's name and the case they have selected in the game.
 */
class Player {
private:
    std::string username; ///< The player's username.
    Case* selectedCase; ///< A pointer to the case selected by the player.

public:
    /**
     * @brief Constructs a Player object with a given username.
     *
     * If no username is provided, defaults to "Player".
     *
     * @param name The username of the player.
     */
    explicit Player(std::string name = "Player");

    /**
     * @brief Copy constructor for Player.
     *
     * Creates a copy of the given Player object.
     *
     * @param other The Player object to copy.
     */
    Player(const Player &other) = default;

    /**
     * @brief Copy assignment operator for Player.
     *
     * Assigns the state of one Player object to another.
     *
     * @param other The Player object to copy.
     * @return A reference to the current Player object.
     */
    Player &operator=(const Player &other) = default;

    /**
     * @brief Destructor for Player.
     *
     * Handles cleanup when a Player object is destroyed.
     */
    ~Player() = default;

    /**
     * @brief Outputs the player's information to a stream.
     *
     * This function displays the player's username.
     *
     * @param os The output stream.
     * @param p The Player object to output.
     * @return The output stream with the player's information.
     */
    friend std::ostream& operator<<(std::ostream &os, const Player &p);

    /**
     * @brief Selects a case for the player.
     *
     * This function sets the player's selected case.
     *
     * @param selectedCase The Case object that the player selects.
     */
    void selectCase(Case* selectedCase);
};

#endif // PLAYER_HPP
