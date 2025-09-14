#include "../includes/Apple.hpp"
#include <iostream>

Apple::Apple()
	: shape(sf::Vector2f(Utils::tileSize, Utils::tileSize))
{
	shape.setFillColor(sf::Color::Red);
	shape.setScale(Utils::scale, Utils::scale);
}

void Apple::spawnAtTile(sf::Vector2i tile) {
	shape.setPosition(tile.x, tile.y);

	std::cout << "Apple spawned at tile: " << tile.x << ", " << tile.y << std::endl;

}

sf::Vector2f Apple::getApplePos() {
	return shape.getPosition();
}

// Override
void Apple::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(shape, states);
};