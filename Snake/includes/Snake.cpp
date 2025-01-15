#include "Snake.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <includes/Tile.h>
using namespace sf;

Snake::Snake(int xStart, int yStart, float tileSize) {

	xTile = xStart;
	yTile = yStart;
	this->tileSize = tileSize;

	RectangleShape segment(Vector2f(tileSize, tileSize));
    segment.setFillColor(Color::Magenta);
    segment.setPosition(xStart * tileSize, yStart * tileSize);
    body.push_back(segment);
}

void Snake::move(Vector2f newPosition) {
	RectangleShape segment = body.front();
	segment.setPosition(newPosition);
	body.insert(body.begin(), segment);
	body.pop_back();
}


void Snake::draw(RenderWindow &window) {
    for (auto &segment : body) {
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

