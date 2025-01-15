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

private:
	sf::RectangleShape tile;
};

#endif