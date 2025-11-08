#include "Menu.hpp"
#include "Utils.hpp"

Menu::Menu(const std::string& title, int titleCharSize, int itemCharSize) :
	m_titleCharSize(titleCharSize),
	m_itemCharSize(itemCharSize),
	m_windowSizeX(Utils::g_mapSizeInTilesX * Utils::g_tileSize),
	m_windowSizeY(Utils::g_mapSizeInTilesY * Utils::g_tileSize),
	m_font("assets/fonts/Chewy/Chewy-Regular.ttf"),
	m_titleText(m_font),
	m_selectedIdx(0)
{
	// Set up title
	m_titleText.setString(title);
	m_titleText.setCharacterSize(m_titleCharSize);
	m_titleText.setStyle(sf::Text::Bold);
	centerOrigin(m_titleText);
	m_titleText.setPosition(sf::Vector2f(m_windowSizeX / 2.0f, m_windowSizeY / 3.8f));
}

void Menu::addMenuItem(const std::string& text, std::function<void()> action) {
	MenuItem menuItem(text, action);
	m_menuItems.push_back(menuItem);

	sf::Text displayText(m_font, text, m_itemCharSize);
	centerOrigin(displayText);
	displayText.setOutlineColor(sf::Color::Blue);

	// Set the position in relation to previous items
	if (m_displayTexts.empty()) {
		displayText.setPosition(sf::Vector2f(m_windowSizeX / 2.0f, m_windowSizeY / 2.0f));
		// Highlight first item by default
		displayText.setOutlineThickness(4);
	}
	else {
		float prevItemX = m_displayTexts.back().getPosition().x;
		float prevItemY = m_displayTexts.back().getPosition().y;
		displayText.setPosition(sf::Vector2f(prevItemX, prevItemY + 75));
	}

	m_displayTexts.push_back(displayText);
}

void Menu::executeSelectedAction() {
	if (m_selectedIdx >= 0 && m_selectedIdx < m_menuItems.size()) {
		m_menuItems[m_selectedIdx].action();
	}
}

void Menu::moveUp() {
	if (m_selectedIdx - 1 >= 0) {
		updateHighlighted(m_selectedIdx - 1, m_selectedIdx);
	}
}

void Menu::moveDown() {
	if (m_selectedIdx + 1 < m_displayTexts.size()) {
		updateHighlighted(m_selectedIdx + 1, m_selectedIdx);
	}
}

void Menu::updateHighlighted(int newIdx, int oldIdx) {
	if (oldIdx >= 0 && oldIdx < m_displayTexts.size() && newIdx >= 0 && newIdx < m_displayTexts.size()) {
		m_displayTexts[oldIdx].setOutlineThickness(0);	// De-highlight the previous item
		m_displayTexts[newIdx].setOutlineThickness(4);	// Highlight the new item
		m_selectedIdx = newIdx;
	}
}

void Menu::centerOrigin(sf::Text& text) {
	sf::FloatRect textRect = text.getLocalBounds();
	sf::Vector2f origin(textRect.size.x / 2.0f, textRect.size.y / 2.0f);
	text.setOrigin(origin);
}

void Menu::draw(sf::RenderWindow& window) {
	if (!m_displayTexts.empty()) {
		window.draw(m_titleText);
		for (const sf::Text& text : m_displayTexts) {
			window.draw(text);
		}
	}
}
