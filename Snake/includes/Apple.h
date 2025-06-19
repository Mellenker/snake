#pragma once

#include <SFML/Graphics.hpp>

class Apple {
public:
	Apple(float tileSize);
	void placeAppleRandomly(int tileSize, int xMax, int yMax);
	std::map<char, int> getAppleCoords();
	void draw(sf::RenderWindow& window);
private:
	sf::RectangleShape apple;
	int xTile;
	int yTile;
};


