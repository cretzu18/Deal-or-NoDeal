#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Case.h"
#include "Player.h"
#include "Banker.h"
#include "Button.h"

enum GameState {
    MENU,
    CASES,
};

class Game {
private:
    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite background;
    Player player;
    std::vector<Case> cases;
    Button playButton;
    int round;
    GameState gameState;

public:
    Game();
    ~Game() = default;

    void play();

private:
    void backgroundMenu();
    void backgroundCases();
    void createCases(std::vector<double> amounts);
    void handleEvents();
    void render();
};

#endif // GAME_HPP
