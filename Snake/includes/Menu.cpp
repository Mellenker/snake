#include "Menu.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

Font font;

Menu::Menu(int windowSizeX, int windowSizeY) 
	: windowSizeX(windowSizeX), windowSizeY(windowSizeY), highlightedIdx(0)
{

	// Initialize font
	font.loadFromFile("resources\\arial.ttf");
}

void Menu::setTitle(std::string title) {
	titleText.setFont(font);
	titleText.setString(title);
	titleText.setCharacterSize(42);
	titleText.setStyle(sf::Text::Bold);

	// Center the origin of the text
	titleText = centerOrigin(titleText);
	// Set the position to the upper center of the window
	titleText.setPosition(windowSizeX / 2.0f, windowSizeY / 2.5f);
}

void Menu::addItem(std::string string) {
	Text itemText = Text(string, font, 30);
	// Center the origin of the text
	itemText = centerOrigin(itemText);

	itemText.setOutlineColor(sf::Color::Blue);

	// Set the position in relation to previous items
	if (items.empty()) {
		itemText.setPosition(windowSizeX / 2.0f, windowSizeY / 2.0f);

		// Highlight first item by default
		itemText.setOutlineThickness(3);
	}
	else {
		float prevItemX = items.back().getPosition().x;
		float prevItemY = items.back().getPosition().y;
		itemText.setPosition(prevItemX, prevItemY + 75);
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

Text Menu::centerOrigin(sf::Text text) {
	FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	return text;
}

void Menu::draw(RenderWindow& window) {
	if (!items.empty()) {
		window.draw(titleText);
		for (Text text : items) {
			window.draw(text);
		}
	}
}
