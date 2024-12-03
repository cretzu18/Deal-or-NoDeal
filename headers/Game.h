#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <vector>
#include "Case.h"
#include "Player.h"
#include "Banker.h"
#include "Settings.h"
#include <memory>

class Game {
private:
    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite background;
    sf::Text gameText;
    sf::Font font;
    sf::Music menuMusic;
    sf::Music gameMusic;
    Settings settings;

    Player player;
    Banker banker;
    std::vector<Case> cases;
    std::vector<std::shared_ptr<Button>> menuButtons;
    int round;
    GameState gameState;

public:
    Game();
    ~Game() = default;

    void play();

private:
    void createButtons();
    void createCases(std::vector<double> amounts);
    void backgroundMenu();
    void backgroundCases();
    void playMenuMusic();
    void playGameMusic();
    void handleEvents(const std::vector<int>& casesPerRound, int& eliminatedCases);
    void render();
};

#endif // GAME_HPP
