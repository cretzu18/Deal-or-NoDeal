#include "../headers/Errors.h"

GameError::GameError(const std::string &message) : std::runtime_error(message) {};

/**
 * @brief Constructs a FontError with a custom error message.
 *
 * This constructor prepends the string "Font error: " to the provided message
 * and passes it to the base class GameError, which creates a FontError exception.
 *
 * @param message The error message specific to the font-related issue.
 */
FontError::FontError(const std::string &message) : GameError(std::string("Font error: ") + message) {};

/**
 * @brief Constructs a MusicError with a custom error message.
 *
 * This constructor prepends the string "Music error: " to the provided message
 * and passes it to the base class GameError, which creates a MusicError exception.
 *
 * @param message The error message specific to the music-related issue.
 */
MusicError::MusicError(const std::string &message) : GameError(std::string("Music error: ") + message) {};

/**
 * @brief Constructs a BackgroundError with a custom error message.
 *
 * This constructor prepends the string "Background error: " to the provided message
 * and passes it to the base class GameError, which creates a BackgroundError exception.
 *
 * @param message The error message specific to the background-related issue.
 */
BackgroundError::BackgroundError(const std::string &message) : GameError(std::string("Background error: ") + message) {};

/**
 * @brief Constructs a TextureError with a custom error message.
 *
 * This constructor prepends the string "Texture error: " to the provided message
 * and passes it to the base class GameError, which creates a TextureError exception.
 *
 * @param message The error message specific to the texture-related issue.
 */
TextureError::TextureError(const std::string &message) : GameError(std::string("Texture error: ") + message) {};
