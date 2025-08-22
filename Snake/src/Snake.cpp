#include "../includes/Snake.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../includes/Tile.hpp"

Snake::Snake(int startPosX, int startPosY)
	: headTilePos(startPosX, startPosY),
	colorHead(sf::Color(103, 0, 255)),
	colorTail(sf::Color(143, 0, 204)),
	currDir(NONE)
{
	std::cout << _MSC_VER << std::endl;
	// Create snake head and tail 
	sf::RectangleShape head(sf::Vector2f(Utils::tileSize, Utils::tileSize));
	sf::RectangleShape tail(sf::Vector2f(Utils::tileSize, Utils::tileSize));

	head.setFillColor(colorHead);
	tail.setFillColor(colorTail);

	head.setPosition(startPosX * Utils::tileSize, startPosY * Utils::tileSize);
	tail.setPosition((startPosX - 1) * Utils::tileSize, startPosY * Utils::tileSize);

	body.push_back(head);
	body.push_back(tail);
}
	
void Snake::move(sf::Vector2f newPosition) {
	std::cout << "Moving snake to: " << newPosition.x << ", " << newPosition.y << std::endl;
	sf::RectangleShape segment = body.front(); // Copy front segment
	segment.setPosition(newPosition);
	body.insert(body.begin(), segment);
	body[1].setFillColor(colorTail);
	tailEnd = body.back().getPosition();
	body.pop_back();
}

sf::Vector2i Snake::getHeadTilePos() {
	return headTilePos;
}

void Snake::setHeadTilePos(sf::Vector2i newHeadTilePos) {
	headTilePos = newHeadTilePos;
}

void Snake::addSegment() {
	sf::RectangleShape segment = body.back(); // Copy front segment
	segment.setPosition(tailEnd);
	segment.setFillColor(colorTail);
	body.insert(body.end(), segment);
}

sf::Vector2f Snake::getTailEnd() {
	return tailEnd;
}

void Snake::changeDir(sf::Keyboard::Key keyPressed) {
	// Handle ingame keyboard input
	switch (keyPressed) {
	case sf::Keyboard::Key::W:
		if (currDir != DOWN) {
			std::cout << "UP" << std::endl;
			currDir = UP;
		}
		break;
	case sf::Keyboard::Key::A:
		if (currDir != RIGHT) {
			std::cout << "UP" << std::endl;
			currDir = LEFT;
		}
		break;
	case sf::Keyboard::Key::S:
		if (currDir != UP) {
			std::cout << "DOWN" << std::endl;
			currDir = DOWN;
		}
		break;
	case sf::Keyboard::Key::D:
		if (currDir != LEFT) {
			std::cout << "RIGHT" << std::endl;
			currDir = RIGHT;
		}
		break;
	default:
		break;
	}
}

void Snake::setDir(Direction newDir) {
	currDir = newDir;
}

enum Snake::Direction Snake::getCurrDir() {
	return currDir;
}

// Override
void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto& segment : body) {
		target.draw(segment, states);
	}
};
