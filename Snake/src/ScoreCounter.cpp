#include <iostream>

#include "../includes/ScoreCounter.hpp"
#include "../includes/Utils.hpp"

ScoreCounter::ScoreCounter() {
	std::cout << "scoreCounter created\n";
	resetPoints();
	
	// Font
	font.loadFromFile("resources\\arial.ttf");
	text.setFont(font);
	text.setCharacterSize(36);
	text.setStyle(sf::Text::Bold);

	// Positioning
	text.setPosition((Utils::mapSizeInTilesX * Utils::tileSize) - Utils::tileSize, 0);

}

void ScoreCounter::addPoint() {
	std::cout << "Point added\n";
	score++;
	text.setString(std::to_string(score));
}

void ScoreCounter::resetPoints() {
	std::cout << "Points reset\n";
	score = 0;
	text.setString(std::to_string(score));
}

void ScoreCounter::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(text, states);
};
