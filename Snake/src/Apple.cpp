#include "includes/Apple.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

using namespace sf;

Apple::Apple(float tileSize)
	: xTile(0), yTile(0), shape(Vector2f(tileSize, tileSize))
{
	shape.setFillColor(Color::Red);
}

void Apple::placeAppleRandomly(int tileSize, int xMax, int yMax) {
	// Generate random coordinates
	std::random_device random;
	std::mt19937 rng(random());
	std::uniform_int_distribution<> disX(0, xMax);
	std::uniform_int_distribution<> disY(0, yMax);
	int randomizedXTile = disX(rng);
	int randomizedYTile = disY(rng);
	int randomizedX = randomizedXTile * tileSize;
	int randomizedY = randomizedYTile * tileSize;

	//std::cout << "X: " << randomizedX << std::endl;
	//std::cout << "Y: " << randomizedY << std::endl;

	shape.setPosition(randomizedX, randomizedY);
	xTile = randomizedXTile;
	yTile = randomizedYTile;
}

std::map<char, int> Apple::getAppleCoords() {
	std::map<char, int> coords = {
		{'x', xTile},
		{'y', yTile}
	};
	return coords;
}

// Override
void Apple::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(shape, states);
};