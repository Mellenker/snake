#include "Menu.hpp"
#include <string>
#include "Utils.hpp"

Menu::Menu(int titleCharSize, int itemCharSize) :
	m_titleCharSize(titleCharSize),
	m_itemCharSize(itemCharSize),
	m_windowSizeX(Utils::g_mapSizeInTilesX* Utils::g_tileSize),
	m_windowSizeY(Utils::g_mapSizeInTilesY* Utils::g_tileSize),
	m_font("assets/fonts/Chewy/Chewy-Regular.ttf"),
	m_titleText(m_font), 
	m_highlightedIdx(0)
{}

void Menu::setTitle(const std::string& title) {
	m_titleText.setString(title);
	m_titleText.setCharacterSize(m_titleCharSize);
	m_titleText.setStyle(sf::Text::Bold);

	centerOrigin(m_titleText);
	m_titleText.setPosition(sf::Vector2f(m_windowSizeX / 2.0f, m_windowSizeY / 3.8f));
}

void Menu::addItem(const std::string& string) {
	sf::Text itemText(m_font, string, m_itemCharSize);
	centerOrigin(itemText);

	itemText.setOutlineColor(sf::Color::Blue);

	// Set the position in relation to previous items
	if (m_items.empty()) {
		itemText.setPosition(sf::Vector2f(m_windowSizeX / 2.0f, m_windowSizeY / 2.0f));

		// Highlight first item by default
		itemText.setOutlineThickness(4);
	}
	else {
		float prevItemX = m_items.back().getPosition().x;
		float prevItemY = m_items.back().getPosition().y;
		itemText.setPosition(sf::Vector2f(prevItemX, prevItemY + 75));
	}

	m_items.push_back(itemText);
}

void Menu::moveUp() {
	if (m_highlightedIdx - 1 >= 0) {
		updateHighlighted(m_highlightedIdx - 1, m_highlightedIdx);
	}
}

void Menu::moveDown() {
	if (m_highlightedIdx + 1 >= 0) {
		updateHighlighted(m_highlightedIdx + 1, m_highlightedIdx);
	}
}

void Menu::updateHighlighted(int newIdx, int oldIdx) {
	if (oldIdx >= 0 && newIdx < m_items.size()) {
		m_items[oldIdx].setOutlineThickness(0);	// De-highlight the previous item
		m_items[newIdx].setOutlineThickness(3);	// Highlight the next item
		m_highlightedIdx = newIdx;
	}
}

int Menu::getHighlightedIdx() {
	return m_highlightedIdx;
}

void Menu::centerOrigin(sf::Text& text) {
	sf::FloatRect textRect = text.getLocalBounds();
	sf::Vector2f origin(textRect.size.x / 2.0f, textRect.size.y / 2.0f);
	text.setOrigin(origin);
}

void Menu::draw(sf::RenderWindow& window) {
	if (!m_items.empty()) {
		window.draw(m_titleText);
		for (sf::Text text : m_items) {
			window.draw(text);
		}
	}
}
