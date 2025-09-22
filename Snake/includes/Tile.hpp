#pragma once

#include <SFML/Graphics.hpp>

class Tile : public sf::Drawable {
public:
	Tile();
	Tile(float size, float xPos, float yPos);
	void setColor(sf::Color color);

private:
	sf::RectangleShape shape;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};