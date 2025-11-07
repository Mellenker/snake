#pragma once
#include <SFML/Graphics.hpp>

class ScoreCounter : public sf::Drawable {
public:
	ScoreCounter();
	void addPoint();
	void resetPoints();
	// virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	int m_score;
	sf::Font m_font;
	sf::Text m_text;
};