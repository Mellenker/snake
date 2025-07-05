#include "includes/Tile.h"
#include <SFML/Graphics.hpp>'
#include <iostream>

using namespace sf;

RectangleShape tile;

// Default constructor
Tile::Tile()
	: shape(Vector2f(30, 30)), occupied(false)
{
	shape.setPosition(Vector2f(0, 0));
}

Tile::Tile(float size, float xPos, float yPos) {
	shape.setSize(Vector2f(size, size));
	shape.setPosition(Vector2f(xPos, yPos));
	occupied = false;
}

void Tile::setColor(Color color) {
	shape.setFillColor(color);
}

void Tile::draw(RenderTexture& texture) {
	texture.draw(shape);
}

Vector2f Tile::getPosition() {
	return shape.getPosition();
}

bool Tile::isOccupied() {
	return occupied;
}

void Tile::setOccupied(bool val) {
	occupied = val;
}
