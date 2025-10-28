#include <SFML/Graphics.hpp>
#include "Snake.hpp"

#include <iostream>

Snake::Snake(int startTilePosX, int startTilePosY)
	: m_headPos(startTilePosX* Utils::g_tileSize, startTilePosY* Utils::g_tileSize),
	m_colorHead(Colors::snakeHead),
	m_colorTail(Colors::snakeTail),
	m_currDir(NONE)
{
	// Create snake head and tail 
	sf::RectangleShape head(sf::Vector2f(Utils::g_tileSize, Utils::g_tileSize));
	sf::RectangleShape tail(sf::Vector2f(Utils::g_tileSize, Utils::g_tileSize));

	head.setFillColor(m_colorHead);
	tail.setFillColor(m_colorTail);

	head.setPosition(m_headPos);
	tail.setPosition(sf::Vector2f(m_headPos.x - Utils::g_tileSize, m_headPos.y));

	m_body.push_back(head);
	m_body.push_back(tail);
}

void Snake::move(sf::Vector2f newPosition) {
	sf::RectangleShape segment = m_body.front(); // Copy front segment
	segment.setPosition(newPosition);
	m_headPos = newPosition;
	m_body.insert(m_body.begin(), segment);
	m_body[1].setFillColor(m_colorTail);
	m_tailEnd = m_body.back().getPosition();
	m_body.pop_back();
}

sf::Vector2f Snake::getHeadPos() {
	return m_headPos;
}

void Snake::addSegment() {
	sf::RectangleShape segment = m_body.back(); // Copy back segment
	segment.setPosition(m_tailEnd);
	segment.setFillColor(m_colorTail);
	m_body.insert(m_body.end(), segment);
}

sf::Vector2f Snake::getTailEnd() {
	return m_tailEnd;
}

void Snake::changeDir(sf::Keyboard::Key keyPressed) {
	// Handle ingame keyboard input
	switch (keyPressed) {
	case sf::Keyboard::Key::W:
		if (m_currDir != DOWN) {
			m_currDir = UP;
		}
		break;
	case sf::Keyboard::Key::A:
		if (m_currDir != RIGHT) {
			m_currDir = LEFT;
		}
		break;
	case sf::Keyboard::Key::S:
		if (m_currDir != UP) {
			m_currDir = DOWN;
		}
		break;
	case sf::Keyboard::Key::D:
		if (m_currDir != LEFT) {
			m_currDir = RIGHT;
		}
		break;
	default:
		break;
	}
}

void Snake::setDir(Direction newDir) {
	m_currDir = newDir;
}

enum Snake::Direction Snake::getCurrDir() {
	return m_currDir;
}

// Override
void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto& segment : m_body) {
		target.draw(segment, states);
	}
};
