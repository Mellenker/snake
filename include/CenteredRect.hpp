#pragma once

#include <SFML/Graphics.hpp>

/*
    A rectangle with a centered origin that can be positioned relative to
    its top-left corner. This allows textures to rotate around the center
    while maintaining position based on the top-left point.
*/

class CenteredRect : public sf::RectangleShape {
public:
    CenteredRect(sf::Vector2f size);

    // Set position based on top left corner of rect
    void setPosFromTopLeft(sf::Vector2f topLeft);

    // Get top left based on position
    sf::Vector2f getTopLeftFromPos();
};
