#include "../headers/Banker.h"

Banker::Banker() {
    acceptButton = std::make_shared<ExitButton>("ACCEPT", 1100, 200, 100, 50);
    rejectButton = std::make_shared<ExitButton>("REJECT", 1300, 200, 100, 50);

    if (!font.loadFromFile("../resources/arial.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        exit(1);
    }
}

std::ostream& operator<<(std::ostream &os, const Banker &b) {
    os << "The banker offered " << b.offersHistory[b.offersHistory.size() - 1] << "$.\n";
    return os;
}

double Banker::offer(const std::vector<Case>& remainingCases) {
    if (remainingCases.empty()) return 0;

    double totalAmount = 0;
    int cnt = 0;
    for (const Case& c : remainingCases)
        if (!c.isEliminated()) {
            totalAmount += c.getAmount();
            cnt++;
        }

    const double average = totalAmount / static_cast<double>(cnt);
    const double minAmount = average * 0.25;
    const double maxAmount = average * 0.35;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(minAmount, maxAmount);
    const double currentOffer = dis(gen);

    offersHistory.push_back(currentOffer);
    return currentOffer;
}

void Banker::clearOffers() {
    for (const auto& offer : offersHistory)
        offersHistory.clear();
}

void Banker::draw(sf::RenderWindow &window) {
    acceptButton->draw(window);
    rejectButton->draw(window);
}

void Banker::drawOffers(sf::RenderWindow &window) {
    sf::Text text;
    text.setFont(font);
    text.setString("Offers history:");
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Yellow);
    text.setPosition(1050, 350);
    window.draw(text);

    std::vector<sf::Text> offersText;
    for (int i = 0; i < offersHistory.size(); i++) {
        sf::Text tmp;
        tmp.setString("$" + std::to_string(static_cast<int>(offersHistory[i])));
        offersText.push_back(tmp);
        offersText.back().setFont(font);
        offersText.back().setCharacterSize(30);
        offersText.back().setFillColor(sf::Color::Yellow);
        offersText.back().setPosition(1050,400 + i * 50);
    }

    for (const sf::Text& txt : offersText)
        window.draw(txt);
}

bool Banker::isAcceptButtonClicked(const sf::RenderWindow& window) const {
    return acceptButton->isClicked(window);
}

bool Banker::isRejectButtonClicked(const sf::RenderWindow& window) const {
    return rejectButton->isClicked(window);
}