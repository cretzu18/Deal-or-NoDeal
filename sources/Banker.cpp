#include "../headers/Banker.h"

/**
 * @brief Default constructor for the Banker class.
 *
 * Initializes the accept and reject buttons and loads the font used for displaying offers.
 *
 * @throws FontError if the font file cannot be loaded.
 */
Banker::Banker()
	: rejectButton (std::make_shared<ExitButton>("REJECT", 1300, 200, 100, 50))
	, acceptButton (std::make_shared<ExitButton>("ACCEPT", 1100, 200, 100, 50))
{
	if (!font.loadFromFile("../resources/arial.ttf"))
		throw FontError("The font could not be loaded!");
}

/**
 * @brief Stream insertion operator for the Banker class.
 *
 * Displays the latest offer made by the banker.
 *
 * @param os The output stream.
 * @param b The banker object.
 * @return A reference to the output stream.
 */
std::ostream& operator<<(std::ostream &os, const Banker &b) {
	os << "The banker offered " << b.offersHistory[b.offersHistory.size() - 1] << "$.\n";
	return os;
}

/**
 * @brief Clears the history of offers made by the banker.
 */
void Banker::clearOffers() {
	offersHistory.clear();
}

/**
 * @brief Draws the accept and reject buttons on the provided window.
 *
 * @param window The SFML render window.
 */
void Banker::draw(sf::RenderWindow &window) const {
	acceptButton->draw(window);
	rejectButton->draw(window);
}

/**
 * @brief Draws the history of offers made by the banker.
 *
 * Displays the list of offers at a specific position in the game window.
 *
 * @param window The SFML render window.
 */
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

/**
 * @brief Checks if the accept button has been clicked.
 *
 * @param window The SFML render window.
 * @return True if the accept button is clicked, otherwise false.
 */
bool Banker::isAcceptButtonClicked(const sf::RenderWindow& window) const {
	return acceptButton->isClicked(window);
}

/**
 * @brief Checks if the reject button has been clicked.
 *
 * @param window The SFML render window.
 * @return True if the reject button is clicked, otherwise false.
 */
bool Banker::isRejectButtonClicked(const sf::RenderWindow& window) const {
	return rejectButton->isClicked(window);
}

/**
 * @brief Calculates an offer that is slightly higher than the average remaining case amounts.
 *
 * - In early rounds (<= 6), the offer is between 30% and 40% of the average.
 * - In later rounds, the offer is between 60% and 75% of the average.
 *
 * @param cases The remaining cases in the game.
 * @param round The current round of the game.
 * @return The calculated offer.
 */
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

/**
 * @brief Calculates a lowball offer to maximize the bank's profit.
 *
 * - In early rounds (<= 6), the offer is between 25% and 35% of the average.
 * - In later rounds, the offer is between 25% and 50% of the average.
 *
 * @param cases The remaining cases in the game.
 * @param round The current round of the game.
 * @return The calculated offer.
 */
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

/**
 * @brief Calculates an offer using a random multiplier for unpredictability.
 *
 * - In early rounds, the offer remains 0 to avoid randomness affecting the beginning.
 * - In later rounds, a random multiplier between 0.25 and 1.5 is applied to the average remaining amount.
 *
 * @param cases The remaining cases in the game.
 * @param round The current round of the game.
 * @return The calculated offer.
 */
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

/**
 * @brief Calculates an offer designed to frustrate the player by being as low as possible.
 *
 * - In early rounds (<= 6), the offer is half of the average of all remaining amounts.
 * - In later rounds, the offer is the lowest remaining amount.
 *
 * @param cases The remaining cases in the game.
 * @param round The current round of the game.
 * @return The calculated offer.
 */
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
		currentOffer = totalAmount / static_cast<double>(cases.size()) * 0.5;
	}
	else {
		currentOffer = minAmount;
	}

	offersHistory.push_back(currentOffer);
	return currentOffer;
}

/**
 * @brief Calculates an offer that helps the player by being relatively generous.
 *
 * - In early rounds, the offer is 50% of the average remaining amount.
 * - In later rounds, a random multiplier between 1.25 and 1.75 is applied to the offer.
 *
 * @param cases The remaining cases in the game.
 * @param round The current round of the game.
 * @return The calculated offer.
 */
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