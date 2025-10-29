#pragma once
#include <SFML/Graphics.hpp>

class Apple : public sf::Drawable {
public:
	Apple();
	void spawnAtTile(sf::Vector2f tile);
	sf::Vector2f getApplePos();
private:
	sf::RectangleShape m_shape;
	static constexpr int initTileX = 0;
	static constexpr int initTileY = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


