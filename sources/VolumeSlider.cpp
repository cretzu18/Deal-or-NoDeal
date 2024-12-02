#include "../headers/VolumeSlider.h"

VolumeSlider::VolumeSlider(const float x, const float y): volumeLevel(100) {
    volumeSlider.setSize(sf::Vector2f(300, 10));
    volumeSlider.setPosition(sf::Vector2f(x, y));
    volumeSlider.setFillColor(sf::Color::White);

    volumeKnob.setSize(sf::Vector2f(20, 20));
    volumeSlider.setFillColor(sf::Color::Red);
    volumeKnob.setPosition(x + (volumeLevel / 100) * 300, y - 10);
}

void VolumeSlider::draw(sf::RenderWindow &window) {
    window.draw(volumeSlider);
    window.draw(volumeKnob);
}

void VolumeSlider::update(const sf::RenderWindow& window, const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            if (volumeSlider.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                const float newLevel = ((mousePosition.x - volumeSlider.getPosition().x) / volumeSlider.getSize().x) * 100;
                volumeLevel = newLevel;
                volumeKnob.setPosition(volumeSlider.getPosition().x + (volumeLevel / 100) * volumeSlider.getSize().x - volumeKnob.getSize().x / 2, volumeKnob.getPosition().y);
            }
        }
    }
}