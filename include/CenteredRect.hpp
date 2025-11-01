#pragma once

#include <SFML/Graphics.hpp>

class CenteredRect : public sf::RectangleShape {
public:
    CenteredRect(const sf::Vector2f& size) {
        setSize(size);
        setOrigin(size / 2.f);
    }

    void setTopLeft(const sf::Vector2f& topLeft) {
        setPosition(topLeft + getSize() / 2.f);
    }
};
