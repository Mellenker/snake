#pragma once
#include <SFML/Graphics.hpp>
#include "CenteredRect.hpp"

class Snake : public sf::Drawable {
public:
	Snake(int startPosX, int startPosY);
	void move(sf::Vector2f newPosition);
	void draw(sf::RenderWindow& window);
	sf::Vector2f getHeadPos();
	sf::Vector2f getLastSegmentPos();
	enum Direction { NONE, UP, LEFT, RIGHT, DOWN };
	void addSegment();
	void setDir(Direction newDir);
	Direction getCurrDir();
	void updateDir(sf::Keyboard::Key keyPressed);
	void rotateSegment(Direction dir, sf::Transformable& segment);
	void updateFaceTexture(std::string filePath);
	void reset();
private:
	int m_startTilePosX;
	int m_startTilePosY;
	sf::Vector2f m_headPos;
	sf::Vector2f m_lastSegmentPos;
	std::vector<CenteredRect> m_body;
	Direction m_currDir;

	sf::Color m_colorHead;
	sf::Color m_colorTail;

	sf::Texture m_faceTexture;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

