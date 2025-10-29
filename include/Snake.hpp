#pragma once
#include <SFML/Graphics.hpp>

class Snake : public sf::Drawable {
public:
	Snake(int startPosX, int startPosY);
	void move(sf::Vector2f newPosition);
	void draw(sf::RenderWindow& window);
	sf::Vector2f getHeadPos();
	sf::Vector2f getTailEnd();
	enum Direction { NONE, UP, LEFT, RIGHT, DOWN };
	void addSegment();
	void setDir(Direction newDir);
	Direction getCurrDir();
	void changeDir(sf::Keyboard::Key keyPressed);

private:
	sf::Vector2f m_headPos;

	sf::Color m_colorHead;
	sf::Color m_colorTail;

	std::vector<sf::RectangleShape> m_body;

	sf::Vector2f m_tailEnd;
	Direction m_currDir;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

