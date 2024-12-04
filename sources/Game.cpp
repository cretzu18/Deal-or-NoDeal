#include "../headers/Game.h"

Game::Game() : window(sf::VideoMode(1600, 900), "Deal or No Deal", sf::Style::Titlebar | sf::Style::Close)
	, round (0)
	, gameState(MENU)
{
	createButtons();
	randomizeBanker();

	if(!menuMusic.openFromFile("./menu.ogg"))
		throw MusicError("No menu music found!");
	menuMusic.setLoop(true);
	if(!gameMusic.openFromFile("./game.ogg"))
		throw MusicError("No game music found!");
	gameMusic.setLoop(true);
	window.setFramerateLimit(60);

	if (!font.loadFromFile("./arial.ttf"))
		throw FontError("The font could not be loaded!");

	gameText.setFont(font);
	gameText.setString("");
	gameText.setCharacterSize(30);
	gameText.setFillColor(sf::Color::Red);
	gameText.setPosition(1050, 150);
}

void Game::play() {
	const std::vector<double> amounts = { 1, 5, 10, 25, 50, 75, 100, 200, 300, 400, 500, 750,
	                                      1000, 5000, 10000, 25000, 50000, 75000, 100000, 200000,
	                                      300000, 400000, 500000, 750000, 1000000
	                                    };
	const std::vector<int> casesPerRound = {6, 5, 4, 3, 2, 1, 1, 1};
	int eliminatedCases = 0;
	bool offered = false;
	int lastOffer = 0;
	bool create = false;

	while (window.isOpen()) {
		if (round == 0)
			create = false;

		if (round == 1 && !create) {
			create = true;
			createCases(amounts);
			randomizeBanker();
			eliminatedCases = 0;
			offered = false;
			lastOffer = 0;
		}
		handleEvents(casesPerRound, eliminatedCases, offered, lastOffer);
		render(offered);
	}

	menuMusic.stop();
	gameMusic.stop();
}

void Game::handleEvents(const std::vector<int>& casesPerRound, int& eliminatedCases, bool& offered, int& lastOffer) {
	sf::Event event{};

	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();

		if (gameState == MENU) {
			playMenuMusic();
			for (const auto & button : menuButtons) {
				if (!std::dynamic_pointer_cast<BackButton>(button) && button->isClicked(window)) {
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
			if (round == 1) {
				gameText.setString("Choose your case!");
				for (auto & it : cases) {
					if (it.isClicked(window)) {
						it.selectCase();
						player.selectCase(&it);
						round++;
						break;
					}
				}
			}
			else if (round >= 2 && round <= 9) {
				const int casesToEliminate = casesPerRound[round - 2];
				if (offered == false) {
					if (casesToEliminate - eliminatedCases == 1)
						gameText.setString("Eliminate " + std::to_string(casesToEliminate - eliminatedCases) + " case!");
					else
						gameText.setString("Eliminate " + std::to_string(casesToEliminate - eliminatedCases) + " cases!");

					for (auto &it : cases) {
						if (it.isClicked(window)) {
							it.eliminateCase();
							eliminatedCases++;
						}
						if (eliminatedCases == casesToEliminate) {
							lastOffer = static_cast<int>(banker->offer(cases, round));
							break;
						}
					}
				}

				if (eliminatedCases == casesToEliminate) {
					gameText.setString("The " + banker->getType() + " offers: $" + std::to_string(static_cast<int>(lastOffer)) + "!");
					offered = true;

					if (banker->isRejectButtonClicked(window)) {
						eliminatedCases = 0;
						offered = false;
						round++;
					}

					if (banker->isAcceptButtonClicked(window)) {
						gameText.setString("You won: $ " + std::to_string(static_cast<int>(lastOffer)) + "!");
						offered = false;
						banker->clearOffers();
						gameState = GAME_OVER;
					}
				}
			}
			else if (round == 10) {
				for (auto &it : cases)
					if (it.isSelected()) {
						it.deselectCase();
						break;
					}

				round++;
			}
			else if (round == 11) {
				gameText.setString("Choose your final case!");
				for (auto &it : cases)
					if (it.isClicked(window)) {
						player.selectCase(&it);
						it.selectCase();
						for (auto &case_ : cases)
							if (!case_.isEliminated() && !case_.isSelected())
								case_.eliminateCase();
						banker->clearOffers();
						gameText.setString("You won: $" + std::to_string(static_cast<int>(it.getAmount())) + " !");
						gameState = GAME_OVER;
					}
			}
		}

		if (gameState == GAME_OVER) {
			for (const auto & button : menuButtons) {
				if (std::dynamic_pointer_cast<BackButton>(button) && button->isClicked(window)) {
					button->action(window, gameState, round);
					break;
				}
			}
		}
	}
}

void Game::render(const bool offered) {
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
			if (!std::dynamic_pointer_cast<BackButton>(button))
				button->draw(window);
	}
	else if (gameState == CASES) {
		for (const Case& c : cases) {
			c.draw(window);
		}
		window.draw(gameText);
		banker->drawOffers(window);
		if (offered == true)
			banker->draw(window);
	}
	else if (gameState == SETTINGS) {
		settings.draw(window);
	}
	else if (gameState == GAME_OVER) {
		for (const Case& c : cases) {
			c.draw(window);
		}
		for (const auto & button : menuButtons)
			if (std::dynamic_pointer_cast<BackButton>(button))
				button->draw(window);
		window.draw(gameText);

	}

	window.display();
}

void Game::backgroundCases() {
	if (!backgroundTexture.loadFromFile("./background2.png")) {
		throw BackgroundError("The background could not be loaded!");
	}
	background.setTexture(backgroundTexture);
}

void Game::backgroundMenu() {
	if (!backgroundTexture.loadFromFile("./background.png")) {
		throw BackgroundError("The background could not be loaded!");
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
		const float x = static_cast<float>(windowSize.x) * 0.03f + (i % 5) * (static_cast<float>(windowSize.x) * 0.10f);
		const float y = static_cast<float>(windowSize.y) * 0.03f + (i / 5)  * (static_cast<float>(windowSize.x) * 0.10f);
		c.setPosition(x, y);
		cases.push_back(c);
	}
}

void Game::createButtons() {
	menuButtons.push_back(std::make_shared<PlayButton>("PLAY", 50, 840, 300, 50));
	menuButtons.push_back(std::make_shared<SettingsButton>("SETTINGS", 650, 840, 300, 50));
	menuButtons.push_back(std::make_shared<ExitButton>("EXIT", 1250, 840, 300, 50));
	menuButtons.push_back(std::make_shared<BackButton>("BACK", 1250, 750, 300, 100));
}

void Game::randomizeBanker() {
	const std::vector<std::function<std::unique_ptr<Banker>()>> allBankers = {
		[]() { return std::make_unique<GenerousBanker>(); },
		[]() { return std::make_unique<GreedyBanker>(); },
		[]() { return std::make_unique<LuckyBanker>(); },
		[]() { return std::make_unique<SadisticBanker>(); },
		[]() { return std::make_unique<HelperBanker>(); }
	};

	banker = allBankers[RandomUtil::getRandomInt(0, static_cast<int>(allBankers.size()) - 1)]();
}
