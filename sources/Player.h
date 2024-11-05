#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <iostream>
#include "Case.h"

class Player {
private:
    std::string username;
    Case* selectedCase;

public:
    explicit Player(std::string name = "Player");
    Player(const Player &other) = default;
    Player &operator=(const Player &other) = default;
    ~Player() = default;

    friend std::ostream& operator<<(std::ostream &os, const Player &p);
    void selectCase(Case* selectedCase);
};

#endif // PLAYER_HPP
