#include "../headers/Player.h"

Player::Player(std::string name) : username(std::move(name)), selectedCase(nullptr) {}

/**
 * @brief Outputs the player's information to an output stream.
 *
 * This function displays the player's username along with a message indicating that the player
 * has selected a case.
 *
 * @param os The output stream.
 * @param p The Player object to output.
 * @return The output stream with the player's information.
 */
std::ostream& operator<<(std::ostream &os, const Player &p) {
    os << p.username << " has selected a case.\n";
    return os;
}

/**
 * @brief Selects a case for the player.
 *
 * This function assigns a selected case to the player.
 * The selected case is set by the pointer `selected`.
 *
 * @param selected The Case object that the player selects.
 */
void Player::selectCase(Case* selected) {
    selectedCase = selected;
}
