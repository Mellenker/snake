#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Snake : public sf::Drawable {
public:
	Snake(float tileSize, int headTileX, int headTileY);
	void move(sf::Vector2f newPosition);
	void draw(sf::RenderWindow& window);
	std::map<char, int> getHeadTileCoords();
	void setHeadTileCoords(int x, int y);
	void addSegment();
	sf::Vector2f getTailEnd();
	enum Direction { UP, LEFT, RIGHT, DOWN, STILL };
	void setDir(Direction newDir);
	Direction getCurrDir();
	void handleInput(sf::Keyboard::Key keyPressed);
	void checkCollision(); // Implement later


private:
	int tileSize;
	int headTileX;
	int headTileY;

	sf::Color colorHead;
	sf::Color colorTail;

	std::vector<sf::RectangleShape> body;

	sf::Vector2f tailEnd;
	Direction currDir;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

