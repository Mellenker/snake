#pragma once

#include <SFML/Graphics.hpp>
#include "includes/Utils.hpp"

class Apple : public sf::Drawable {
public:
	Apple();
	void spawnAtRandomTile(int xMax, int yMax);
	sf::Vector2i getAppleTilePos();
	void draw(sf::RenderWindow& window);
private:
	sf::RectangleShape shape;
	static constexpr int initTileX = 0;
	static constexpr int initTileY = 0;
	sf::Vector2i appleTilePos;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


