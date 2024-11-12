#include "../headers/Player.h"

Player::Player(std::string name) : username(std::move(name)), selectedCase(nullptr) {}

std::ostream& operator<<(std::ostream &os, const Player &p) {
    os << p.username << " has selected a case.\n";
    return os;
}

void Player::selectCase(Case* selected) {
    selectedCase = selected;
}
