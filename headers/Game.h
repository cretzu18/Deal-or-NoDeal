#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include "Case.h"
#include "Player.h"
#include "Banker.h"
#include "Settings.h"


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
    std::unique_ptr<Banker> banker;
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
    void handleEvents(const std::vector<int>& casesPerRound, int& eliminatedCases, bool& offered, int& lastOffer);
    void render(bool offered);
    void randomizeBanker();
};

#endif // GAME_HPP
