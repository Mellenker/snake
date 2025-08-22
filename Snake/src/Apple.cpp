#include "../includes/Apple.hpp"
#include <iostream>
#include <random>

Apple::Apple()
	: appleTilePos(initTileX, initTileY), shape(sf::Vector2f(Utils::tileSize, Utils::tileSize))
{
	shape.setFillColor(sf::Color::Red);
}

// MAKE SURE IT DOESN'T SPAWN ON TOP OF THE SNAKE
void Apple::spawnAtRandomTile(int xMax, int yMax) {
	// Generate random coordinates
	std::random_device random;
	std::mt19937 rng(random());
	std::uniform_int_distribution<> disX(0, xMax);
	std::uniform_int_distribution<> disY(0, yMax);
	int randomizedXTile = disX(rng);
	int randomizedYTile = disY(rng);
	int randomizedX = randomizedXTile * Utils::tileSize;
	int randomizedY = randomizedYTile * Utils::tileSize;

	shape.setPosition(randomizedX, randomizedY);
	appleTilePos = sf::Vector2i(randomizedXTile, randomizedYTile);

}

sf::Vector2i Apple::getAppleTilePos() {
	return appleTilePos;
}

// Override
void Apple::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(shape, states);
};