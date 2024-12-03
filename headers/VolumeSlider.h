#ifndef VOLUMESLIDER_H
#define VOLUMESLIDER_H

#include <SFML/Graphics.hpp>

class VolumeSlider {
    sf::RectangleShape volumeSlider;
    sf::RectangleShape volumeKnob;
    float volumeLevel;

public:
    VolumeSlider(float x, float y);
    ~VolumeSlider() = default;
    float getVolumeLevel() const { return volumeLevel; }
    void draw(sf::RenderWindow &window) const;
    void update(const sf::RenderWindow& window, const sf::Event& event);
};

#endif
