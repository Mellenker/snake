#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <vector>

class Snake {
public:
	Snake(int xStart, int yStart, float tileSize);
	void move(sf::Vector2f newPosition);
	void draw(sf::RenderWindow& window);
	std::map<char, int> getHeadTileCoords();
	void setHeadTileCoords(int x, int y);


private:
	std::vector<sf::RectangleShape> body;
	sf::Vector2f movement;
	std::map<char, int> segmentTileCoords;
	int xTile;
	int yTile;
	float tileSize;
};

#endif
