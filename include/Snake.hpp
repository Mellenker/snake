#pragma once
#include <SFML/Graphics.hpp>
#include "CenteredRect.hpp"

class Snake : public sf::Drawable {
public:
	Snake(int startPosX, int startPosY);
	void move(sf::Vector2f newPosition);
	void addSegment();
	enum Direction { NONE, UP, LEFT, RIGHT, DOWN };
	Direction getCurrDir();
	void setDir(Direction newDir);
	void updateDir(sf::Keyboard::Key keyPressed);
	sf::Vector2f getHeadPos();
	sf::Vector2f getLastSegmentPos();
	void updateFaceTexture(std::string filePath);
	void draw(sf::RenderWindow& window);
	void reset();
private:
	void rotateSegment(Direction dir, sf::Transformable& segment);

	std::vector<CenteredRect> m_body;
	sf::Vector2f m_headPos;
	sf::Vector2f m_lastSegmentPos;
	Direction m_currDir;
	int m_startTilePosX;
	int m_startTilePosY;

	sf::Texture m_faceTexture;
	sf::Color m_colorBody;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

