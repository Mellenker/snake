#include "ScoreCounter.hpp"

ScoreCounter::ScoreCounter()
	: font("resources/arial.ttf"),
	text(font)
{
	resetPoints();
	
	// Font
	text.setFont(font);
	text.setCharacterSize(36);
	text.setStyle(sf::Text::Bold);

	// Positioning
	text.setPosition(sf::Vector2f((Utils::mapSizeInTilesX * Utils::tileSize) - Utils::tileSize, 0));

}

void ScoreCounter::addPoint() {
	score++;
	text.setString(std::to_string(score));
}

void ScoreCounter::resetPoints() {
	score = 0;
	text.setString(std::to_string(score));
}

void ScoreCounter::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(text, states);
};
