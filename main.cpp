#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
//#include "SFML/Audio.hpp"

class Case {
    //int caseNumber;
    double amount;
    bool selected;
    sf::Sprite sprite;
    sf::Texture texture;

    //static int totalCases;

public:
    explicit Case(const double money = 0): amount(money), selected(false) {
        //caseNumber = ++totalCases;

        if (!texture.loadFromFile("../images/case.png")) {
            std::cout << "Failed to load case" << std::endl;
            exit(1);
        }

        sprite.setTexture(texture);
        sprite.scale(0.3, 0.3);
    }

    Case(const Case &other) {
        //caseNumber = ++totalCases;
        amount = other.amount;
        selected = other.selected;
        sprite = other.sprite;
        texture = other.texture;

        sprite.setTexture(texture);
    }

    Case& operator=(const Case &other) {
        //caseNumber = ++totalCases;
        amount = other.amount;
        selected = other.selected;
        sprite = other.sprite;
        texture = other.texture;

        sprite.setTexture(texture);

        return *this;
    }

    ~Case() = default;
        //totalCases--;


    friend std::ostream &operator<<(std::ostream &os, const Case &c) {
        os << "The case has " << c.amount << "$.\n" ;
        return os;
    }

    double getAmount() const {
        return amount;
    }

    void selectCase() {
        selected = true;
        sprite.setColor(sf::Color::Red);
    }

    void draw(sf::RenderWindow &window) const {
        window.draw(sprite);
    }

    void setPosition(const float x, const float y) {
        sprite.setPosition(x, y);
    }

    bool isMouseOver(const sf::RenderWindow& window) const {
        if (selected == true)
            return false;
        const sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        const sf::FloatRect bounds = sprite.getGlobalBounds();
        return bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    }

    bool isClicked(const sf::RenderWindow& window) const {
        return isMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
    }
};

class Player {
    std::string username;
    Case* selectedCase;
    bool acceptOffer;

public:
    explicit Player(std::string  name = "Player")
        : username(std::move(name)), selectedCase(nullptr), acceptOffer(false) {}

    Player(const Player &other) = default;
    Player &operator=(const Player &other) = default;
    ~Player() = default;

    friend std::ostream& operator<<(std::ostream &os, const Player &p) {
        os << p.username << " has selected a case.\n";
        return os;
    }

    void selectCase(Case* selectedCase) {
        this->selectedCase = selectedCase;
    }
};

class Banker {
    double currentOffer;
    std::vector<double> offersHistory;

public:
    Banker() : currentOffer(0) {};

    Banker(const Banker &other) = default;
    Banker &operator=(const Banker &other) = default;
    ~Banker() = default;

    friend std::ostream& operator<<(std::ostream &os, const Banker &b) {
        os << "The banker offered " << b.currentOffer << "$.\n";
        return os;
    }

    void offer(const std::vector<Case>& remainingCases) {
        if (remainingCases.empty()) {
            return;
        }

        double totalAmount = 0;
        for (const Case& c : remainingCases) {
            totalAmount += c.getAmount();
        }

        const double average = totalAmount / static_cast<double>(remainingCases.size());
        const double minAmount = average * 0.75;
        const double maxAmount = average * 1.1;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(minAmount, maxAmount);
        const double currentOffer = dis(gen);

        offersHistory.push_back(currentOffer);
    }
};


class Button {
    sf::RectangleShape button;
    sf::Text buttonText;
    sf::Font font;

public:
    explicit Button(const std::string& text = "", const float posX = 0, const float posY = 0, const float width = 100, const float height = 100) {
        if (!font.loadFromFile("../font/OakleyRidge.ttf")) {
            std::cerr << "Failed to load font." << std::endl;
            exit(1);
        }

        button.setSize(sf::Vector2f(width, height));
        button.setPosition(posX, posY);
        button.setFillColor(sf::Color(255, 255, 102));
        button.setOutlineColor(sf::Color::Black);
        button.setOutlineThickness(1);
        button.setPosition(posX, posY);

        buttonText.setFont(font);
        buttonText.setString(text);
        buttonText.setCharacterSize(30);
        buttonText.setFillColor(sf::Color::Black);
        const sf::FloatRect textBounds = buttonText.getGlobalBounds();
        buttonText.setPosition(posX + width / 2 - textBounds.width / 2,
                               posY + height / 2 - textBounds.height / 2);
    }

    Button(const Button& other) {
        button = other.button;
        buttonText = other.buttonText;
        font = other.font;
        buttonText.setFont(font);
    }

    Button& operator=(const Button& other) {
        if (this != &other) {
            button = other.button;
            buttonText = other.buttonText;
            font = other.font;
            buttonText.setFont(font);
        }

        return *this;
    }

    ~Button() = default;

    friend std::ostream& operator<<(std::ostream& os, const Button& button) {
        os << "You pressed the " << button.buttonText.getString().toAnsiString() << " button.\n";
        return os;
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(button);
        window.draw(buttonText);
    }

    bool isMouseOver(const sf::RenderWindow& window) const {
        const sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        const sf::FloatRect buttonBounds = button.getGlobalBounds();

        return buttonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    }

    bool isClicked(const sf::RenderWindow& window) const {
        return isMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
    }
};


enum GameState {
    MENU,
    CASES,
};

class Game {
    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite background;
    Player player;
    //Banker banker;
    std::vector<Case> cases;
    Button playButton;
    int round;
    GameState gameState;

public:
    Game() : window(sf::VideoMode(1600, 900), "Deal or No Deal", sf::Style::Titlebar | sf::Style::Close)
           , playButton("Play", window.getSize().x * 0.1, window.getSize().y * 0.9, 300, 50)
           , round (0)
           , gameState (MENU)
    {
        window.setFramerateLimit(60);
    }

    ~Game() = default;

    void play() {
        const std::vector<double> amounts = { 0.1, 1, 5, 10, 25, 50, 75, 100, 200, 300, 400, 500, 750,
                                            1000, 5000, 10000, 25000, 50000, 75000, 100000, 200000,
                                            300000, 400000, 500000, 750000, 1000000};
        createCases(amounts);
        while (window.isOpen()) {
            if (round == 1)
                createCases(amounts);
            handleEvents();
            render();
        }
    }

private:
    void createCases(std::vector<double> amounts) {
        cases.clear();
        std::random_device rd;
        std::mt19937 gen {rd()};

        std::ranges::shuffle(amounts, gen);

        for (size_t i = 0; i < amounts.size(); ++i) {
            Case c(amounts[i]);
            c.setPosition(100 + (i%5) * 150, 100 + (i/5) * 120);
            cases.push_back(c);
        }
    }

    void backgroundCases() {
        if (!backgroundTexture.loadFromFile("../images/background2.png")) {
            std::cerr << "Failed to load background.png." << std::endl;
            exit(1);
        }
        background.setTexture(backgroundTexture);
    }

    void backgroundMenu() {
        if (!backgroundTexture.loadFromFile("../images/background.png")) {
            std::cerr << "Failed to load background.png." << std::endl;
            exit(1);
        }
        background.setTexture(backgroundTexture);
    }

    void handleEvents() {
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

    void render() {
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
            for (Case& c : cases) {
                c.draw(window);
            }
        }

        window.display();
    }
};

int main() {
    Game game;
    game.play();

    return 0;
}