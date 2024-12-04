#include "../headers/Errors.h"

GameError::GameError(const std::string &message) : std::runtime_error(message) {};

FontError::FontError(const std::string &message) : GameError(std::string("Font error: ") + message) {};

MusicError::MusicError(const std::string &message) : GameError(std::string("Music error: ") + message) {};

BackgroundError::BackgroundError(const std::string &message) : GameError(std::string("Background error: ") + message) {};

TextureError::TextureError(const std::string &message) : GameError(std::string("Texture error: ") + message) {};
