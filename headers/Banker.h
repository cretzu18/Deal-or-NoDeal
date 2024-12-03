#ifndef BANKER_HPP
#define BANKER_HPP

#include <vector>
#include <random>
#include <iostream>
#include <memory>
#include <functional>

#include "Button.h"
#include "Case.h"
#include "RandomUtil.h"

/**
 * @brief Base class representing a Banker in the game.
 *
 * The Banker class handles the calculation of offers, rendering of accept/reject buttons,
 * and maintains the history of offers. It is designed to be extended by derived classes
 * that provide specific offer calculation strategies.
 */
class Banker {
private:
    std::shared_ptr<Button> rejectButton; ///< Button to reject the banker's offer.
    std::shared_ptr<Button> acceptButton; ///< Button to accept the banker's offer.
    sf::Font font; ///< Font used for rendering text.

protected:
    std::vector<double> offersHistory; ///< Stores the history of all offers made by the banker.

public:
    /**
     * @brief Default constructor for Banker.
     * Initializes the accept and reject buttons.
     */
    Banker();

    Banker(const Banker &other) = default; ///< Default copy constructor.
    Banker &operator=(const Banker &other) = default; ///< Default copy assignment operator.
    virtual ~Banker() = default; ///< Virtual destructor for polymorphism.

    /**
     * @brief Overloaded output operator for displaying banker details.
     * @param os The output stream.
     * @param b The banker object.
     * @return The modified output stream.
     */
    friend std::ostream& operator<<(std::ostream &os, const Banker &b);

    /**
     * @brief Pure virtual method to calculate the banker's offer.
     * @param cases The remaining cases in the game.
     * @param round The current round of the game.
     * @return The offer amount.
     */
    virtual double offer(const std::vector<Case>& cases, int round) = 0;

    /**
     * @brief Clears the history of offers.
     */
    void clearOffers();

    /**
     * @brief Draws the accept and reject buttons on the window.
     * @param window The render window.
     */
    void draw(sf::RenderWindow &window) const;

    /**
     * @brief Displays the history of offers made by the banker.
     * @param window The render window.
     */
    void drawOffers(sf::RenderWindow &window) const;

    /**
     * @brief Checks if the accept button was clicked.
     * @param window The render window.
     * @return True if the accept button was clicked, false otherwise.
     */
    bool isAcceptButtonClicked(const sf::RenderWindow& window) const;

    /**
     * @brief Checks if the reject button was clicked.
     * @param window The render window.
     * @return True if the reject button was clicked, false otherwise.
     */
    bool isRejectButtonClicked(const sf::RenderWindow &window) const;

    /**
     * @brief Pure virtual method to get the type of banker as a string.
     * @return The type of the banker.
     */
    virtual std::string getType() const = 0;

    /**
     * @brief Pure virtual method to clone the banker object.
     * @return A pointer to the cloned banker object.
     */
    virtual Banker* clone() = 0;
};

/**
 * @brief Represents a Banker who makes higher-than-average offers.
 *
 * The GenerousBanker calculates offers based on a formula that
 * emphasizes the higher remaining amounts, encouraging the player
 * with relatively lucrative deals.
 */
class GenerousBanker final : public Banker {
public:
	/**
	 * @brief Clones the GenerousBanker object.
	 * @return A pointer to the cloned GenerousBanker object.
	 */
	[[maybe_unused]] GenerousBanker* clone() override {
		return new GenerousBanker(*this);
	}

	/**
	 * @brief Calculates the offer based on a generous formula.
	 *
	 * The GenerousBanker considers the average of the remaining
	 * case amounts and increases it slightly to provide more appealing offers.
	 *
	 * @param cases The remaining cases in the game.
	 * @param round The current round of the game.
	 * @return The offer amount.
	 */
	[[nodiscard]] double offer(const std::vector<Case>& cases, int round) override;

	/**
	 * @brief Gets the type of banker.
	 * @return The string "Generous Banker".
	 */
	[[nodiscard]] std::string getType() const override {
		return "Generous Banker";
	}
};

/**
 * @brief Represents a Banker who makes lowball offers.
 *
 * The GreedyBanker aims to maximize the bank's profit by making
 * offers significantly lower than the average remaining amounts.
 */
class GreedyBanker final : public Banker {
public:
	/**
	 * @brief Clones the GreedyBanker object.
	 * @return A pointer to the cloned GreedyBanker object.
	 */
	 [[maybe_unused]] GreedyBanker* clone() override {
		return new GreedyBanker(*this);
	}

	/**
	 * @brief Calculates the offer based on a greedy formula.
	 *
	 * The GreedyBanker uses the average of the remaining case amounts
	 * and reduces it considerably to discourage the player from accepting the deal.
	 *
	 * @param cases The remaining cases in the game.
	 * @param round The current round of the game.
	 * @return The offer amount.
	 */
	[[nodiscard]] double offer(const std::vector<Case>& cases, int round) override;

	/**
	 * @brief Gets the type of banker.
	 * @return The string "Greedy Banker".
	 */
	[[nodiscard]] std::string getType() const override {
		return "Greedy Banker";
	};
};

/**
 * @brief Represents a Banker whose offers are influenced by random chance.
 *
 * The LuckyBanker applies a random multiplier to the average
 * of the remaining case amounts, resulting in unpredictable offers.
 */
class LuckyBanker final : public Banker {
	double multiplier; ///< Random multiplier applied to offers.
public:
	/**
	 * @brief Constructs a LuckyBanker with a default multiplier of 1.
	 */
	LuckyBanker() : multiplier(1) {}

	/**
	 * @brief Clones the LuckyBanker object.
	 * @return A pointer to the cloned LuckyBanker object.
	 */
	[[maybe_unused]] LuckyBanker* clone() override {
		return new LuckyBanker(*this);
	}

	/**
	 * @brief Calculates the offer based on a random multiplier.
	 *
	 * The LuckyBanker multiplies the average of the remaining amounts by a random
	 * factor, making the offers highly unpredictable and luck-dependent.
	 *
	 * @param cases The remaining cases in the game.
	 * @param round The current round of the game.
	 * @return The offer amount.
	 */
	[[nodiscard]] double offer(const std::vector<Case>& cases, int round) override;

	/**
	 * @brief Gets the type of banker.
	 * @return The string "Lucky Banker".
	 */
	[[nodiscard]] std::string getType() const override {
		return "Lucky Banker";
	}
};

/**
 * @brief Represents a Banker who makes the worst possible offers.
 *
 * The SadisticBanker focuses on frustrating the player by making
 * offers that are significantly lower than expected.
 */
class SadisticBanker final : public Banker {
public:
	/**
	 * @brief Clones the SadisticBanker object.
	 * @return A pointer to the cloned SadisticBanker object.
	 */
	[[maybe_unused]] SadisticBanker* clone() override {
		return new SadisticBanker(*this);
	}

	/**
	 * @brief Calculates the offer based on a sadistic formula.
	 *
	 * The SadisticBanker makes offers using the minimum remaining
	 * case amount or a fraction of the average, ensuring very low offers.
	 *
	 * @param cases The remaining cases in the game.
	 * @param round The current round of the game.
	 * @return The offer amount.
	 */
	[[nodiscard]] double offer(const std::vector<Case>& cases, int round) override;

	/**
	 * @brief Gets the type of banker.
	 * @return The string "Sadistic Banker".
	 */
	[[nodiscard]] std::string getType() const override {
		return "Sadistic Banker";
	}
};

/**
 * @brief Represents a Banker who supports the player with generous offers.
 *
 * The HelperBanker makes offers that scale positively with the
 * remaining case amounts, often erring on the player's side.
 */
class HelperBanker final : public Banker {
	double multiplier; ///< Multiplier applied to offers to make them more generous.
public:
	/**
	 * @brief Constructs a HelperBanker with a default multiplier of 1.
	 */
	HelperBanker() : multiplier(1) {};

	/**
	 * @brief Clones the HelperBanker object.
	 * @return A pointer to the cloned HelperBanker object.
	 */
	[[maybe_unused]] HelperBanker* clone() override {
		return new HelperBanker(*this);
	}

	/**
	 * @brief Calculates the offer based on a helpful formula.
	 *
	 * The HelperBanker multiplies the average of the remaining amounts
	 * by a favorable factor to create appealing offers for the player.
	 *
	 * @param cases The remaining cases in the game.
	 * @param round The current round of the game.
	 * @return The offer amount.
	 */
	[[nodiscard]] double offer(const std::vector<Case>& cases, int round) override;

	/**
	 * @brief Gets the type of banker.
	 * @return The string "Helper Banker".
	 */
	[[nodiscard]] std::string getType() const override {
		return "Helper Banker";
	}
};

#endif // BANKER_HPP
