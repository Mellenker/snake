#pragma once

#include <SFML/Graphics.hpp>

class Tile : public sf::Drawable {
public:
	Tile();
	Tile(float size, float xPos, float yPos);
	void setColor(sf::Color color);
	void draw(sf::RenderTexture& texture); // MAKE INHERIT DRAWABLE INSTEAD
	sf::Vector2f getPosition();
	bool isOccupied();
	void setOccupied(bool val);

private:
	sf::RectangleShape shape;
	bool occupied;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};