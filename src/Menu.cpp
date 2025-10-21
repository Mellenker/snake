#include "Menu.hpp"
#include <string>

Menu::Menu()
	: windowSizeX(Utils::mapSizeInTilesX* Utils::tileSize),
	windowSizeY(Utils::mapSizeInTilesY* Utils::tileSize),
	font("resources/arial.ttf"),
	titleText(font),
	highlightedIdx(0)
{}

void Menu::setTitle(std::string title) {
	titleText.setString(title);
	titleText.setCharacterSize(42);
	titleText.setStyle(sf::Text::Bold);

	centerOrigin(titleText);
	titleText.setPosition(sf::Vector2f(windowSizeX / 2.0f, windowSizeY / 3.0f));
}

void Menu::addItem(std::string string) {
	sf::Text itemText(font, string, 30);
	centerOrigin(itemText);

	itemText.setOutlineColor(sf::Color::Blue);

	// Set the position in relation to previous items
	if (items.empty()) {
		itemText.setPosition(sf::Vector2f(windowSizeX / 2.0f, windowSizeY / 2.0f));

		// Highlight first item by default
		itemText.setOutlineThickness(3);
	}
	else {
		float prevItemX = items.back().getPosition().x;
		float prevItemY = items.back().getPosition().y;
		itemText.setPosition(sf::Vector2f(prevItemX, prevItemY + 75));
	}

	items.push_back(itemText);
}

void Menu::moveUp() {
	if (highlightedIdx - 1 >= 0) {
		updateHighlighted(highlightedIdx - 1, highlightedIdx);
	}
}

void Menu::moveDown() {
	if (highlightedIdx + 1 >= 0) {
		updateHighlighted(highlightedIdx + 1, highlightedIdx);
	}
}

void Menu::updateHighlighted(int newIdx, int oldIdx) {
	if (oldIdx >= 0 && newIdx < items.size()) {
		items[oldIdx].setOutlineThickness(0);	// De-highlight the previous item
		items[newIdx].setOutlineThickness(3);	// Highlight the next item
		highlightedIdx = newIdx;
	}
}

int Menu::getHighlightedIdx() {
	return highlightedIdx;
}

void Menu::centerOrigin(sf::Text& text) {
	sf::FloatRect textRect = text.getLocalBounds();
	sf::Vector2f origin(textRect.size.x / 2.0f, textRect.size.y / 2.0f);
	text.setOrigin(origin);
}

void Menu::draw(sf::RenderWindow& window) {
	if (!items.empty()) {
		window.draw(titleText);
		for (sf::Text text : items) {
			window.draw(text);
		}
	}
}
