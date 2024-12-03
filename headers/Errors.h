#ifndef ERRORS_H
#define ERRORS_H

#include <stdexcept>
#include <string>

/**
 * @class GameError
 * @brief A custom exception class for general game-related errors.
 *
 * This class extends the standard C++ runtime_error and is used for throwing and catching errors
 * related to the game's functionality, providing a descriptive error message.
 */
class GameError : public std::runtime_error {
public:
    /**
     * @brief Constructs a GameError with a message.
     *
     * This constructor allows the creation of a GameError exception with a specific message describing the error.
     *
     * @param message The error message.
     */
    explicit GameError(const std::string& message);
};

/**
 * @class FontError
 * @brief A custom exception class for font-related errors.
 *
 * This class is derived from GameError and specifically handles errors that occur when loading fonts.
 */
class FontError final : public GameError {
public:
    /**
     * @brief Constructs a FontError with a message.
     *
     * This constructor allows the creation of a FontError exception with a specific message describing the font error.
     *
     * @param message The error message.
     */
    explicit FontError(const std::string& message);
};

/**
 * @class MusicError
 * @brief A custom exception class for music-related errors.
 *
 * This class is derived from GameError and specifically handles errors that occur when loading or playing music.
 */
class MusicError final : public GameError {
public:
    /**
     * @brief Constructs a MusicError with a message.
     *
     * This constructor allows the creation of a MusicError exception with a specific message describing the music error.
     *
     * @param message The error message.
     */
    explicit MusicError(const std::string& message);
};

/**
 * @class BackgroundError
 * @brief A custom exception class for background-related errors.
 *
 * This class is derived from GameError and specifically handles errors related to loading or displaying backgrounds.
 */
class BackgroundError final : public GameError {
public:
    /**
     * @brief Constructs a BackgroundError with a message.
     *
     * This constructor allows the creation of a BackgroundError exception with a specific message describing the background error.
     *
     * @param message The error message.
     */
    explicit BackgroundError(const std::string& message);
};

/**
 * @class TextureError
 * @brief A custom exception class for texture-related errors.
 *
 * This class is derived from GameError and specifically handles errors related to loading textures.
 */
class TextureError final : public GameError {
public:
    /**
     * @brief Constructs a TextureError with a message.
     *
     * This constructor allows the creation of a TextureError exception with a specific message describing the texture error.
     *
     * @param message The error message.
     */
    explicit TextureError(const std::string& message);
};

#endif //ERRORS_H
