#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

class Tile {
public:
	Tile();
	Tile(float size, float xPos, float yPos);
	void setColor(sf::Color color);
	void draw(sf::RenderTexture& texture);
	sf::Vector2f getPosition();
	bool isOccupied();
	void setOccupied(bool val);

private:
	sf::RectangleShape shape;
	bool occupied;
};

#endif