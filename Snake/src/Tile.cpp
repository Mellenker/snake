#include "../includes/Tile.hpp"
#include <SFML/Graphics.hpp>'
#include <iostream>

sf::RectangleShape tile;

Tile::Tile()
	: shape(sf::Vector2f(30, 30))
{
	shape.setPosition(sf::Vector2f(0, 0));
}

Tile::Tile(float size, float xPos, float yPos) {
	shape.setSize(sf::Vector2f(size, size));
	shape.setPosition(sf::Vector2f(xPos, yPos));
}

void Tile::setColor(sf::Color color) {
	shape.setFillColor(color);
}

// Override
void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(shape, states);
};
