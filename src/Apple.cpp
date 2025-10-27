#include "Apple.hpp"

Apple::Apple()
	: m_shape(sf::Vector2f(Utils::g_tileSize, Utils::g_tileSize))
{
	m_shape.setFillColor(Colors::appleColor);
}

void Apple::spawnAtTile(sf::Vector2f tile) {
	m_shape.setPosition(sf::Vector2f(tile.x, tile.y));
}

sf::Vector2f Apple::getApplePos() {
	return m_shape.getPosition();
}

// Override
void Apple::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_shape, states);
};