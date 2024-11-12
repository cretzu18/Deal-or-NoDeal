#include "../headers/Game.h"

Game::Game() : window(sf::VideoMode(1600, 900), "Deal or No Deal", sf::Style::Titlebar | sf::Style::Close)
           , playButton("Play", static_cast<float>(window.getSize().x * 0.1), static_cast<float>(window.getSize().y * 0.9), 300, 50)
           , round (0)
           , gameState (MENU)
{
    window.setFramerateLimit(60);
}

void Game::play() {
    const std::vector<double> amounts = { 0.1, 1, 5, 10, 25, 50, 75, 100, 200, 300, 400, 500, 750,
                                        1000, 5000, 10000, 25000, 50000, 75000, 100000, 200000,
                                        300000, 400000, 500000, 750000, 1000000};
    //createCases(amounts);
    while (window.isOpen()) {
        if (round == 1)
            createCases(amounts);
        handleEvents();
        render();
    }
}

void Game::handleEvents() {
    sf::Event event{};
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (gameState == MENU && playButton.isClicked(window)) {
            round = 1;
            std::cout << playButton;
            gameState = CASES;
        }

        if (gameState == CASES) {
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
    else if (gameState == MENU) {
        backgroundMenu();
    }

    window.draw(background);

    if (gameState == MENU) {
        playButton.draw(window);
    }
    else if (gameState == CASES) {
        for (const Case& c : cases) {
            c.draw(window);
        }
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

void Game::createCases(std::vector<double> amounts) {
    cases.clear();
    std::random_device rd;
    std::mt19937 gen {rd()};

    std::ranges::shuffle(amounts, gen);

    for (size_t i = 0; i < amounts.size(); ++i) {
        Case c(amounts[i]);
        c.setPosition(static_cast<float>(100 + (i%5) * 150), static_cast<float>(100 + static_cast<int>(i/5) * 120));
        cases.push_back(c);
    }
}