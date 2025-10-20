#include "Apple.hpp"

Apple::Apple()
	: shape(sf::Vector2f(Utils::tileSize, Utils::tileSize))
{
	shape.setFillColor(Colors::appleColor);
}

void Apple::spawnAtTile(sf::Vector2f tile) {
	shape.setPosition(sf::Vector2f(tile.x, tile.y));
}

sf::Vector2f Apple::getApplePos() {
	return shape.getPosition();
}

// Override
void Apple::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(shape, states);
};