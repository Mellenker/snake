#include "Tile.h"
#include <SFML/Graphics.hpp>

using namespace sf;

RectangleShape tile;

// Default constructor
Tile::Tile() {
	tile.setSize(Vector2f(30, 30));
	tile.setPosition(Vector2f(0, 0));
}

Tile::Tile(float size, float xPos, float yPos) {
	tile.setSize(Vector2f(size, size));
	tile.setPosition(Vector2f(xPos, yPos));
}

void Tile::setColor(Color color) {
	tile.setFillColor(color);
}
void Tile::draw(RenderTexture& texture) {
	texture.draw(tile);
}

Vector2f Tile::getPosition() {
	return tile.getPosition();
}
