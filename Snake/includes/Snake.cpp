#include "Snake.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

Snake::Snake() {
    RectangleShape segment(Vector2f(30.f, 30.f));
    segment.setFillColor(Color::Magenta);
    segment.setPosition(100.f, 100.f);
    body.push_back(segment);
    direction = Vector2f(20.f, 0.f);
}

void Snake::move(Keyboard::Key key) {
	switch (key) {
		case Keyboard::Key::W:
			direction = Vector2f(0, -0.1f);
			break;
		case Keyboard::Key::A:
			direction = Vector2f(-0.1f, 0);
			break;
		case Keyboard::Key::S:
			direction = Vector2f(0, 0.1f);
			break;
		case Keyboard::Key::D:
			direction = Vector2f(0.1f, 0);
			break;
	}

	RectangleShape segment = body.front();
	
	segment.setPosition(segment.getPosition() + direction);

	body.insert(body.begin(), segment);
	body.pop_back();
}

void Snake::draw(RenderWindow &window) {
    for (auto &segment : body) {
        window.draw(segment);
    }
}

Vector2f Snake::getHeadPosition() {
	Vector2f position = body.front().getPosition();
	return position;
}
void Snake::collideWallY() {
	body.front().setPosition(720, body.front().getPosition().y);
	std::cout << (body.front().getPosition().y);
}
void Snake::collideWallX() {
	body.front().setPosition(body.front().getPosition().y, 720);
}
