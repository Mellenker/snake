#include "includes/Tile.hpp"
#include <SFML/Graphics.hpp>'
#include <iostream>

sf::RectangleShape tile;

// Default constructor
Tile::Tile()
	: shape(sf::Vector2f(30, 30)), occupied(false)
{
	shape.setPosition(sf::Vector2f(0, 0));
}

Tile::Tile(float size, float xPos, float yPos) {
	shape.setSize(sf::Vector2f(size, size));
	shape.setPosition(sf::Vector2f(xPos, yPos));
	occupied = false;
}

void Tile::setColor(sf::Color color) {
	shape.setFillColor(color);
}

sf::Vector2f Tile::getPosition() {
	return shape.getPosition();
}

bool Tile::isOccupied() {
	return occupied;
}

void Tile::setOccupied(bool val) {
	occupied = val;
}

// Override
void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(shape, states);
};
