#include "../headers/Banker.h"

Banker::Banker() {
    acceptButton = std::make_shared<ExitButton>("ACCEPT", 1100, 200, 100, 50);
    rejectButton = std::make_shared<ExitButton>("REJECT", 1300, 200, 100, 50);

    if (!font.loadFromFile("../resources/arial.ttf"))
        throw FontError("The font could not be loaded!");
}

std::ostream& operator<<(std::ostream &os, const Banker &b) {
    os << "The banker offered " << b.offersHistory[b.offersHistory.size() - 1] << "$.\n";
    return os;
}

void Banker::clearOffers() {
    offersHistory.clear();
}

void Banker::draw(sf::RenderWindow &window) const {
    acceptButton->draw(window);
    rejectButton->draw(window);
}

void Banker::drawOffers(sf::RenderWindow &window) const {
    sf::Text text;
    text.setFont(font);
    text.setString("Offers history:");
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Yellow);
    text.setPosition(1050, 350);
    window.draw(text);

    std::vector<sf::Text> offersText;
    for (unsigned long i = 0; i < offersHistory.size(); i++) {
        sf::Text tmp;
        tmp.setString("$" + std::to_string(static_cast<int>(offersHistory[i])));
        offersText.push_back(tmp);
        offersText.back().setFont(font);
        offersText.back().setCharacterSize(30);
        offersText.back().setFillColor(sf::Color::Yellow);
        offersText.back().setPosition(1050,static_cast<float>(400 + i * 50));
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

double GenerousBanker::offer(const std::vector<Case>& cases, const int round) {
    if (cases.empty()) return 0;

    double totalAmount = 0;
    int cnt = 0;
    for (const Case& c : cases)
        if (!c.isEliminated()) {
            totalAmount += c.getAmount();
            cnt++;
        }

    const double average = totalAmount / static_cast<double>(cnt);
    double minAmount, maxAmount;
    if (round <= 6) {
        minAmount = average * 0.3;
        maxAmount = average * 0.4;
    }
    else {
        minAmount = average * 0.6;
        maxAmount = average * 0.75;
    }

    const double currentOffer = RandomUtil::getRandomDouble(minAmount, maxAmount);

    offersHistory.push_back(currentOffer);
    return currentOffer;
}

double GreedyBanker::offer(const std::vector<Case>& cases, const int round) {
    if (cases.empty()) return 0;

    double totalAmount = 0;
    int cnt = 0;
    for (const Case& c : cases)
        if (!c.isEliminated()) {
            totalAmount += c.getAmount();
            cnt++;
        }

    const double average = totalAmount / static_cast<double>(cnt);
    double minAmount, maxAmount;
    if (round <= 6) {
        minAmount = average * 0.25;
        maxAmount = average * 0.35;
    }
    else {
        minAmount = average * 0.25;
        maxAmount = average * 0.5;
    }

    const double currentOffer = RandomUtil::getRandomDouble(minAmount, maxAmount);

    offersHistory.push_back(currentOffer);
    return currentOffer;
}

double LuckyBanker::offer(const std::vector<Case>& cases, const int round) {
    if (cases.empty()) return 0;

    double totalAmount = 0;
    int cnt = 0;
    for (const Case& c : cases)
        if (!c.isEliminated()) {
            totalAmount += c.getAmount();
            cnt++;
        }

    double currentOffer = 0;
    if (round >= 2) {
        multiplier = RandomUtil::getRandomDouble(0.25, 1.5);
        currentOffer = (totalAmount / static_cast<double>(cnt)) * multiplier;
    }

    offersHistory.push_back(currentOffer);
    return currentOffer;
}

double SadisticBanker::offer(const std::vector<Case> &cases, const int round) {
    if (cases.empty()) return 0;

    double minAmount = cases[0].getAmount(), totalAmount = 0;
    for (const Case& c : cases)
        if (!c.isEliminated()) {
            if (minAmount > c.getAmount())
                minAmount = c.getAmount();
            totalAmount += c.getAmount();
        }

    double currentOffer;
    if (round <= 6) {
        currentOffer = totalAmount / static_cast<double>(cases.size());
    }
    else {
        currentOffer = minAmount;
    }

    offersHistory.push_back(currentOffer);
    return currentOffer;
}

double HelperBanker::offer(const std::vector<Case>& cases, const int round) {
    if (cases.empty()) return 0;

    double totalAmount = 0;
    int cnt = 0;
    for (const Case& c : cases)
        if (!c.isEliminated()) {
            totalAmount += c.getAmount();
            cnt++;
        }

    const double average = totalAmount / static_cast<double>(cnt);
    double currentOffer = average * 0.5;

    if (round > 6) {
        multiplier = RandomUtil::getRandomDouble(1.25, 1.75);
        currentOffer *= multiplier;
    }

    offersHistory.push_back(currentOffer);
    return currentOffer;
}