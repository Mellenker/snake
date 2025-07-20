#include "includes/Snake.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <includes/Tile.h>

using namespace sf;

Snake::Snake(float tileSize, int startPosX, int startPosY)
	: tileSize(tileSize),
	headTileX(startPosX),
	headTileY(startPosY),
	colorHead(Color(103, 0, 255)),
	colorTail(Color(143, 0, 204)),
	currDir(STILL)
{

	// Create snake head and tail 
	RectangleShape head(Vector2f(tileSize, tileSize));
	RectangleShape tail(Vector2f(tileSize, tileSize));

	head.setFillColor(colorHead);
	tail.setFillColor(colorTail);

	head.setPosition(startPosX * tileSize, startPosY * tileSize);
	tail.setPosition((startPosX - 1) * tileSize, startPosY * tileSize);

	body.push_back(head);
	body.push_back(tail);
}

void Snake::move(Vector2f newPosition) {
	RectangleShape segment = body.front(); // Copy front segment
	segment.setPosition(newPosition);
	body.insert(body.begin(), segment);
	body[1].setFillColor(colorTail);
	tailEnd = body.back().getPosition();
	body.pop_back();
}

/*
void Snake::draw(RenderWindow& window) {
	for (auto& segment : body) {
		window.draw(segment);
	}
}
*/

std::map<char, int> Snake::getHeadTileCoords() {
	std::map<char, int> coords = {
		{'x', headTileX},
		{'y', headTileY}
	};
	return coords;
}

void Snake::setHeadTileCoords(int x, int y) {
	headTileX = x;
	headTileY = y;
}

void Snake::addSegment() {
	RectangleShape segment = body.back(); // Copy front segment
	segment.setPosition(tailEnd);
	segment.setFillColor(colorTail);
	body.insert(body.end(), segment);
}

Vector2f Snake::getTailEnd() {
	return tailEnd;
}

void Snake::handleInput(Keyboard::Key keyPressed) {
	// Handle ingame keyboard input
	switch (keyPressed) {
	case Keyboard::Key::W:
		if (currDir != DOWN) {
			std::cout << "UP" << std::endl;
			currDir = UP;
		}
		break;
	case Keyboard::Key::A:
		if (currDir != RIGHT) {
			std::cout << "UP" << std::endl;
			currDir = LEFT;
		}
		break;
	case Keyboard::Key::S:
		if (currDir != UP) {
			std::cout << "DOWN" << std::endl;
			currDir = DOWN;
		}
		break;
	case Keyboard::Key::D:
		if (currDir != LEFT) {
			std::cout << "RIGHT" << std::endl;
			currDir = RIGHT;
		}
		break;
	default:
		break;
	}
	return;
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
