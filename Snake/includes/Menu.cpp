#include "Menu.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

Font font;

Menu::Menu(int windowSizeX, int windowSizeY) {
	this->windowSizeX = windowSizeX;
	this->windowSizeY = windowSizeY;

	// Create menu panel
	texture.create(windowSizeX / 3, windowSizeY / 2);
	
	menuPanel.setTexture(texture.getTexture());

	FloatRect menuRect = menuPanel.getLocalBounds();
	menuPanel.setOrigin(menuRect.left + menuRect.width / 2.0f, menuRect.top + menuRect.height / 2.0f);
	menuPanel.setPosition(windowSizeX / 2.0f, windowSizeY / 2.0f);	// Set the position to the center of the window

	curItemIdx = 0;

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
	std::cout << "Move Up" << std::endl;
	if (curItemIdx - 1 >= 0) {
		updateHighlighted(curItemIdx - 1, curItemIdx);
	}
}

void Menu::moveDown() {
	std::cout << "Move Down" << std::endl;
	if (curItemIdx + 1 >= 0) {
		updateHighlighted(curItemIdx + 1, curItemIdx);
	}
}

void Menu::updateHighlighted(int newIdx, int oldIdx) {
	std::cout << items.size() << std::endl;
	if (oldIdx >= 0 && newIdx < items.size()) {
		std::cout << newIdx << std::endl;
		std::cout << oldIdx << std::endl;
		items[oldIdx].setOutlineThickness(0);	// De-highlight the previous item
		items[newIdx].setOutlineThickness(3);	// Highlight the next item
	}
}

Text Menu::centerOrigin(sf::Text text) {
	FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	return text;
}

// Clear and then draw changes to texture
void Menu::updateTexture() {

	texture.clear();

	if (!items.empty()) {
		texture.draw(titleText);
		for (Text text : items) {
			texture.draw(text);
		}
	}
	menuPanel.setTexture(texture.getTexture());
	std::cout << "TEXTURE UPDATED" << std::endl;
}

void Menu::drawToWindow(RenderWindow& window) {
	window.draw(menuPanel);
}
