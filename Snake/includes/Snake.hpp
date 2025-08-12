#pragma once

#include <SFML/Graphics.hpp>
#include "includes/Utils.hpp"
#include <vector>

class Snake : public sf::Drawable {
public:
	Snake(int startPosX, int startPosY);
	void move(sf::Vector2f newPosition);
	void draw(sf::RenderWindow& window);
	sf::Vector2i getHeadTilePos();
	void setHeadTilePos(sf::Vector2i newHeadPos);
	void addSegment();
	sf::Vector2f getTailEnd();
	enum Direction { NONE, UP, LEFT, RIGHT, DOWN };
	void setDir(Direction newDir);
	Direction getCurrDir();
	void changeDir(sf::Keyboard::Key keyPressed);


private:
	sf::Vector2i headTilePos;

	sf::Color colorHead;
	sf::Color colorTail;

	std::vector<sf::RectangleShape> body;

	sf::Vector2f tailEnd;
	Direction currDir;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

