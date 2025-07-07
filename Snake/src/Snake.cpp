#include "includes/Snake.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <includes/Tile.h>
using namespace sf;

Snake::Snake(float tileSize, int xStart, int yStart, Color headColor, Color tailColor)
	: tileSize(tileSize), headTileX(xStart), headTileY(yStart), headColor(headColor), tailColor(tailColor)
{

	// Create snake head and tail 
	RectangleShape head(Vector2f(tileSize, tileSize));
	RectangleShape tail(Vector2f(tileSize, tileSize));

	head.setFillColor(headColor);
	tail.setFillColor(tailColor);

	head.setPosition(xStart * tileSize, yStart * tileSize);
	tail.setPosition((xStart - 1) * tileSize, yStart * tileSize);

	body.push_back(head);
	body.push_back(tail);
}

void Snake::move(Vector2f newPosition) {
	RectangleShape segment = body.front(); // Copy front segment
	segment.setPosition(newPosition);
	body.insert(body.begin(), segment);
	body[1].setFillColor(tailColor);
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
	segment.setFillColor(tailColor);
	body.insert(body.end(), segment);
}

Vector2f Snake::getTailEnd() {
	return tailEnd;
}

// Override
void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto& segment : body) {
		target.draw(segment, states);
	}
};

