#ifndef ERRORS_H
#define ERRORS_H

#include <stdexcept>
#include <string>

class GameError : public std::runtime_error {
public:
    explicit GameError(const std::string& message);
};

class FontError final : public GameError {
public:
    explicit FontError(const std::string& message);
};

class MusicError final : public GameError {
public:
    explicit MusicError(const std::string& message);
};

class BackgroundError final : public GameError {
public:
    explicit BackgroundError(const std::string& message);
};

class TextureError final : public GameError {
public:
    explicit TextureError(const std::string& message);
};

#endif //ERRORS_H
