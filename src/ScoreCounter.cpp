#include "ScoreCounter.hpp"
#include "Utils.hpp"

ScoreCounter::ScoreCounter()
	: m_font("assets/arial.ttf"),
	m_text(m_font)
{
	resetPoints();
	
	// Font
	m_text.setFont(m_font);
	m_text.setCharacterSize(36);
	m_text.setStyle(sf::Text::Bold);

	// Positioning
	m_text.setPosition(sf::Vector2f((Utils::g_mapSizeInTilesX * Utils::g_tileSize) - Utils::g_tileSize, 0));

}

void ScoreCounter::addPoint() {
	m_score++;
	m_text.setString(std::to_string(m_score));
}

void ScoreCounter::resetPoints() {
	m_score = 0;
	m_text.setString(std::to_string(m_score));
}

void ScoreCounter::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_text, states);
};
