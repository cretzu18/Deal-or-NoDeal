#include "../headers/Game.h"

Game::Game() : window(sf::VideoMode(1600, 900), "Deal or No Deal", sf::Style::Titlebar)
               , round (0)
               , gameState(MENU)
{
    createButtons();
    if(!menuMusic.openFromFile("../resources/menu.ogg"))
        exit(1);
    menuMusic.setLoop(true);
    if(!gameMusic.openFromFile("../resources/game.ogg"))
        exit(1);
    gameMusic.setLoop(true);
    window.setFramerateLimit(60);
}

void Game::play() {
    const std::vector<double> amounts = { 0.1, 1, 5, 10, 25, 50, 75, 100, 200, 300, 400, 500, 750,
                                        1000, 5000, 10000, 25000, 50000, 75000, 100000, 200000,
                                        300000, 400000, 500000, 750000, 1000000};
    std::vector<int> casesPerRound = {6, 5, 4, 3, 2, 1, 1, 1, 1};

    while (window.isOpen()) {
        if (round == 1)
            createCases(amounts);
        handleEvents();
        render();
    }

    menuMusic.stop();
    gameMusic.stop();
}

void Game::handleEvents() {
    sf::Event event{};
    while (window.pollEvent(event)) {
         if (gameState == MENU) {
             playMenuMusic();
             for (const auto & button : menuButtons) {
                 if (button->isClicked(window)) {
                     button->action(window, gameState, round);
                     break;
                 }
             }
         }


        if(gameState == SETTINGS) {
            settings.update(window, event, gameState);
            menuMusic.setVolume(settings.getMenuVolumeLevel());
            gameMusic.setVolume(settings.getGameVolumeLevel());
        }

        if (gameState == CASES) {
            playGameMusic();
            if (round == 1)
                for (auto & it : cases) {
                    if (it.isClicked(window)) {
                        it.selectCase();
                        player.selectCase(&it);
                        round++;
                        std::cout << player;
                        break;
                    }
                }
            else if (round == 2) {
                for (auto it = cases.begin(); it != cases.end(); ) {
                    if (it->isClicked(window)) {
                        std::cout << *it;
                        it = cases.erase(it);
                    } else {
                        ++it;
                    }
                }
                if (cases.size() == 1) {
                    std::cout << "Your case: " << cases[0];
                    cases.erase(cases.begin());
                    round++;
                }
            }
            else if (round == 3)
                gameState = MENU;
        }
    }
}

void Game::render() {
    window.clear();

    if (gameState == CASES) {
        backgroundCases();
    }
    else if (gameState == MENU || gameState == SETTINGS) {
        backgroundMenu();
    }

    window.draw(background);

    if (gameState == MENU) {
        for (const auto & button : menuButtons)
                button->draw(window);
    }
    else if (gameState == CASES) {
        for (const Case& c : cases) {
            c.draw(window);
        }
    }
    else {
        settings.draw(window);
    }

    window.display();
}

void Game::backgroundCases() {
    if (!backgroundTexture.loadFromFile("../resources/background2.png")) {
        std::cerr << "Failed to load background.png." << std::endl;
        exit(1);
    }
    background.setTexture(backgroundTexture);
}

void Game::backgroundMenu() {
    if (!backgroundTexture.loadFromFile("../resources/background.png")) {
        std::cerr << "Failed to load background.png." << std::endl;
        exit(1);
    }
    background.setTexture(backgroundTexture);
}

void Game::playMenuMusic() {
    if (menuMusic.getStatus() != sf::Music::Playing) {
        gameMusic.stop();
        menuMusic.play();
    }
}

void Game::playGameMusic() {
    if (gameMusic.getStatus() != sf::Music::Playing) {
        menuMusic.stop();
        gameMusic.play();
    }
}

void Game::createCases(std::vector<double> amounts) {
    cases.clear();
    std::random_device rd;
    std::mt19937 gen {rd()};

    std::ranges::shuffle(amounts, gen);

    const sf::Vector2u windowSize = window.getSize();
    for (size_t i = 0; i < amounts.size(); ++i) {
        Case c(amounts[i]);
        const float x = static_cast<float>(windowSize.x) * 0.03f + (i % 5) * (static_cast<float>(windowSize.x) * 0.09f);
        const float y = static_cast<float>(windowSize.y) * 0.03f + (i / 5)  * (static_cast<float>(windowSize.x) * 0.09f);
        c.setPosition(x, y);
        cases.push_back(c);
    }
}

void Game::createButtons() {
    menuButtons.push_back(std::make_shared<PlayButton>("PLAY", 50, 750, 300, 100));
    menuButtons.push_back(std::make_shared<SettingsButton>("SETTINGS", 650, 750, 300, 100));
    menuButtons.push_back(std::make_shared<ExitButton>("EXIT", 1250, 750, 300, 100));
}
