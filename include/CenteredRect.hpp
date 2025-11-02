#pragma once

#include <SFML/Graphics.hpp>

/*
    Rectangle with centered origin but that can be positioned
    relative to its top left corner.
*/

class CenteredRect : public sf::RectangleShape {
public:
    CenteredRect(const sf::Vector2f& size) {
        setSize(size);
        setOrigin(size / 2.f);
    }

    // Set position based on top left corner of rect
    void setPosFromTopLeft(const sf::Vector2f& topLeft) {
        setPosition(topLeft + getSize() / 2.f);
    }

    // Get top left based on position
    sf::Vector2f getTopLeftFromPos() {
        return (getPosition() - getSize() / 2.f);
    }
};
