#include <SFML/Graphics.hpp>
#include "Snake.hpp"

#include <iostream>

Snake::Snake(int startTilePosX, int startTilePosY)
	: headPos(startTilePosX* Utils::tileSize, startTilePosY* Utils::tileSize),
	colorHead(Colors::snakeHead),
	colorTail(Colors::snakeTail),
	currDir(NONE)
{
	// Create snake head and tail 
	sf::RectangleShape head(sf::Vector2f(Utils::tileSize, Utils::tileSize));
	sf::RectangleShape tail(sf::Vector2f(Utils::tileSize, Utils::tileSize));

	head.setFillColor(colorHead);
	tail.setFillColor(colorTail);

	head.setPosition(headPos);
	tail.setPosition(sf::Vector2f(headPos.x - Utils::tileSize, headPos.y));

	body.push_back(head);
	body.push_back(tail);
}

void Snake::move(sf::Vector2f newPosition) {
	sf::RectangleShape segment = body.front(); // Copy front segment
	segment.setPosition(newPosition);
	headPos = newPosition;
	body.insert(body.begin(), segment);
	body[1].setFillColor(colorTail);
	tailEnd = body.back().getPosition();
	body.pop_back();
}

sf::Vector2f Snake::getHeadPos() {
	return headPos;
}

void Snake::addSegment() {
	sf::RectangleShape segment = body.back(); // Copy back segment
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
			std::cout << "UP" << "\n";
			currDir = UP;
		}
		break;
	case sf::Keyboard::Key::A:
		if (currDir != RIGHT) {
			std::cout << "LEFT" << "\n";
			currDir = LEFT;
		}
		break;
	case sf::Keyboard::Key::S:
		if (currDir != UP) {
			std::cout << "DOWN" << "\n";
			currDir = DOWN;
		}
		break;
	case sf::Keyboard::Key::D:
		if (currDir != LEFT) {
			std::cout << "RIGHT" << "\n";
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
