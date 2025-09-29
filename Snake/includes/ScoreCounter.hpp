#pragma once

#include <SFML/Graphics.hpp>
#include "../includes/Utils.hpp"

class ScoreCounter : public sf::Drawable {
public:
	ScoreCounter();
	void addPoint();
	void resetPoints();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	int score;
	sf::Text text;
	sf::Font font;
};