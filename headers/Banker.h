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

class Banker {
private:
	std::shared_ptr<Button> rejectButton;
	std::shared_ptr<Button> acceptButton;
	sf::Font font;

protected:
	std::vector<double> offersHistory;

public:
	Banker();
	Banker(const Banker &other) = default;
	Banker &operator=(const Banker &other) = default;
	virtual ~Banker() = default;

	friend std::ostream& operator<<(std::ostream &os, const Banker &b);
	virtual double offer(const std::vector<Case>& cases, int round) = 0;
	void clearOffers();
	void draw(sf::RenderWindow &window) const;
	void drawOffers(sf::RenderWindow &window) const;
	bool isAcceptButtonClicked(const sf::RenderWindow& window) const;
	bool isRejectButtonClicked(const sf::RenderWindow &window) const;
	virtual std::string getType() const = 0;
	virtual Banker* clone() = 0;
};

class GenerousBanker final : public Banker {
public:
	GenerousBanker* clone() override {
		return new GenerousBanker(*this);
	}
	[[nodiscard]] double offer(const std::vector<Case>& cases, int round) override;
	[[nodiscard]] std::string getType() const override {
		return "Generous Banker";
	};
};

class GreedyBanker final : public Banker {
public:
	[[maybe_unused]] GreedyBanker* clone() override {
		return new GreedyBanker(*this);
	}
	[[nodiscard]] double offer(const std::vector<Case>& cases, int round) override;
	[[nodiscard]] std::string getType() const override {
		return "Greedy Banker";
	};
};

class LuckyBanker final : public Banker {
	double multiplier;
public:
	LuckyBanker() : multiplier(1) {}
	[[maybe_unused]] LuckyBanker* clone() override {
		return new LuckyBanker(*this);
	}
	[[nodiscard]] double offer(const std::vector<Case>& cases, int round) override;
	[[nodiscard]] std::string getType() const override {
		return "Lucky Banker";
	}
};

class SadisticBanker final : public Banker {
public:
	[[maybe_unused]] SadisticBanker* clone() override {
		return new SadisticBanker(*this);
	}
	[[nodiscard]] double offer(const std::vector<Case>& cases, int round) override;
	[[nodiscard]] std::string getType() const override {
		return "Sadistic Banker";
	}
};

class HelperBanker final : public Banker {
	double multiplier;
public:
	HelperBanker() : multiplier(1) {};
	[[maybe_unused]] HelperBanker* clone() override {
		return new HelperBanker(*this);
	}
	[[nodiscard]] double offer(const std::vector<Case>& cases, int round) override;
	[[nodiscard]] std::string getType() const override {
		return "Helper Banker";
	}
};

#endif // BANKER_HPP
