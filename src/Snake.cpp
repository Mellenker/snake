#include "Snake.hpp"
#include "Utils.hpp"
#include "Colors.hpp"
#include "CenteredRect.hpp"

Snake::Snake(int startTilePosX, int startTilePosY) :
	m_headStartTilePosX(startTilePosX),
	m_headStartTilePosY(startTilePosY),
	m_colorBody(Colors::snakeBody),
	m_currDir(NONE),
	m_faceTexture("assets/textures/snake_face_alive.png")
{
	m_faceTexture.setSmooth(true);
	reset();
}

// Adds new segment at the front and deletes the last segment
void Snake::move(sf::Vector2f newPosition) {
	CenteredRect segment = m_body.front();
	segment.setPosFromTopLeft(newPosition);
	m_body.insert(m_body.begin(), segment);
	m_body[1].setFillColor(m_colorBody);
	m_body[1].setTexture(nullptr);
	m_body.pop_back();
}

sf::Vector2f Snake::getHeadPos() {
	return m_body[0].getTopLeftFromPos();
}

void Snake::addSegment() {
	CenteredRect segment = m_body.back();
	segment.setFillColor(m_colorBody);
	segment.setPosFromTopLeft(getLastSegmentPos()); // Add on top of last segment
	m_body.insert(m_body.end(), segment);
}

sf::Vector2f Snake::getLastSegmentPos() {
	return m_body.back().getTopLeftFromPos();
}

void Snake::updateDir(sf::Keyboard::Key keyPressed) {
	// Handle ingame keyboard input
	switch (keyPressed) {
	case sf::Keyboard::Key::W:
		if (m_currDir != DOWN)
			m_currDir = UP;
		break;
	case sf::Keyboard::Key::A:
		if ((m_currDir != RIGHT) && (m_currDir != NONE))
			m_currDir = LEFT;
		break;
	case sf::Keyboard::Key::S:
		if (m_currDir != UP)
			m_currDir = DOWN;
		break;
	case sf::Keyboard::Key::D:
		if (m_currDir != LEFT)
			m_currDir = RIGHT;
		break;
	default:
		break;
	}
	// Rotate face with direction
	rotateSegment(m_currDir, m_body[0]);
}

void Snake::rotateSegment(Direction dir, sf::Transformable& segment) {
	switch(dir) {
		case UP:
			segment.setRotation(sf::degrees(270));
			break;
		case RIGHT:
			segment.setRotation(sf::degrees(0));
			break;
		case DOWN:
			segment.setRotation(sf::degrees(90));
			break;
		case LEFT:
			segment.setRotation(sf::degrees(180));
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

void Snake::reset() {
	m_body.clear();

	// Initialize head
	CenteredRect head(sf::Vector2f(Utils::g_tileSize, Utils::g_tileSize));
	head.setPosFromTopLeft(sf::Vector2f(
		m_headStartTilePosX * Utils::g_tileSize,
		m_headStartTilePosY * Utils::g_tileSize
	));
	updateFaceTexture("assets/textures/snake_face_alive.png");
	head.setTexture(&m_faceTexture);
	m_body.push_back(head);

	// Initialize tail
	CenteredRect tail(sf::Vector2f(Utils::g_tileSize, Utils::g_tileSize));
	tail.setPosFromTopLeft(sf::Vector2f(
		getHeadPos().x - Utils::g_tileSize, 
		getHeadPos().y
	));
	tail.setFillColor(m_colorBody);
	m_body.push_back(tail);
}

// Override
void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto& segment : m_body) {
		target.draw(segment, states);
	}
};

void Snake::updateFaceTexture(std::string filePath) {
	if (!m_faceTexture.loadFromFile(filePath)) {
		throw std::runtime_error("Failed to load snake face texture");
	}
}
