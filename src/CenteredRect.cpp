#include "CenteredRect.hpp"

CenteredRect::CenteredRect(const sf::Vector2f& size)
{
    setSize(size);
    setOrigin(size / 2.f);
}

void CenteredRect::setPosFromTopLeft(const sf::Vector2f& topLeft) {
    setPosition(topLeft + getSize() / 2.f);
}

sf::Vector2f CenteredRect::getTopLeftFromPos() {
    return (getPosition() - getSize() / 2.f);
}