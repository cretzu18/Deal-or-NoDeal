#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include "Case.h"
#include "Player.h"
#include "Banker.h"
#include "Settings.h"

/**
 * @class Game
 * @brief Manages the core logic, rendering, and events of the Deal or No Deal game.
 */
class Game {
private:
    sf::RenderWindow window; ///< The main game window.
    sf::Texture backgroundTexture; ///< Texture for the game background.
    sf::Sprite background; ///< Sprite to display the background.
    sf::Text gameText; ///< Text element for displaying messages to the player.
    sf::Font font; ///< Font used for game text.
    sf::Music menuMusic; ///< Music played in the menu.
    sf::Music gameMusic; ///< Music played during gameplay.
    Settings settings; ///< Manages game settings like volume and preferences.

    Player player; ///< Represents the player's state and actions.
    std::unique_ptr<Banker> banker; ///< Banker for calculating offers.
    std::vector<Case> cases; ///< Collection of cases in the game.
    std::vector<std::shared_ptr<Button>> menuButtons; ///< Buttons in the main menu.
    int round; ///< Current game round.
    GameState gameState; ///< Current state of the game (menu, gameplay, etc.).

public:
    /**
     * @brief Constructs a new Game object, initializing all resources and state.
     */
    Game();

    /**
     * @brief Default destructor.
     */
    ~Game() = default;

    /**
     * @brief Main loop for running the game.
     */
    void play();

private:
    /**
     * @brief Creates buttons for the game menu.
     */
    void createButtons();

    /**
     * @brief Creates the cases with randomized amounts.
     *
     * @param amounts The amounts to be assigned to the cases.
     */
    void createCases(std::vector<double> amounts);

    /**
     * @brief Configures the background for the main menu.
     */
    void backgroundMenu();

    /**
     * @brief Configures the background for the case selection and gameplay.
     */
    void backgroundCases();

    /**
     * @brief Plays music for the main menu.
     */
    void playMenuMusic();

    /**
     * @brief Plays music during gameplay.
     */
    void playGameMusic();

    /**
     * @brief Handles events and updates the game state during gameplay.
     *
     * @param casesPerRound Number of cases to eliminate in each round.
     * @param eliminatedCases Reference to the number of cases eliminated in the current round.
     * @param offered Reference to whether an offer has been made.
     * @param lastOffer Reference to the last offer made by the banker.
     */
    void handleEvents(const std::vector<int>& casesPerRound, int& eliminatedCases, bool& offered, int& lastOffer);

    void renderRemainingAmounts(std::vector<double> amounts, std::map <double, std::reference_wrapper<Case>>& map);

    /**
     * @brief Renders the game elements.
     *
     * @param offered Boolean indicating if an offer has been made.
     * @param amounts Amounts of the cases that can be won
     */
    void render(bool offered, std::vector<double> amounts, std::map <double, std::reference_wrapper<Case>>& map);

    /**
     * @brief Randomly assigns a Banker type to the game.
     */
    void randomizeBanker();
};

#endif // GAME_HPP
