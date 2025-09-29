#include "../includes/Apple.hpp"

Apple::Apple()
	: shape(sf::Vector2f(Utils::tileSize, Utils::tileSize))
{
	shape.setFillColor(sf::Color::Red);
}

void Apple::spawnAtTile(sf::Vector2f tile) {
	shape.setPosition(tile.x, tile.y);
}

sf::Vector2f Apple::getApplePos() {
	return shape.getPosition();
}

// Override
void Apple::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(shape, states);
};