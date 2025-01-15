#include "Snake.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <includes/Tile.h>
using namespace sf;

Snake::Snake(int xStart, int yStart, float tileSize, Color headColor, Color tailColor) {

	xTile = xStart;
	yTile = yStart;
	this->headColor = headColor;
	this->tailColor = tailColor;

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
	RectangleShape segment = body.front();
	segment.setPosition(newPosition);
	body.insert(body.begin(), segment);
	body[1].setFillColor(tailColor);
	body.pop_back();
}


void Snake::draw(RenderWindow& window) {
	for (auto& segment : body) {
		window.draw(segment);
	}
}

std::map<char, int> Snake::getHeadTileCoords() {
	std::map<char, int> coords = {
		{'x', xTile},
		{'y', yTile}
	};
	return coords;
}

void Snake::setHeadTileCoords(int x, int y) {
	xTile = x;
	yTile = y;
}

