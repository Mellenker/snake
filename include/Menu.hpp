#pragma once  

#include <SFML/Graphics.hpp>
#include "Utils.hpp"

// Parent class for menus
class Menu {
public:
	Menu();
	void setTitle(std::string title);
	void addItem(std::string string);
	void draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();
	void updateHighlighted(int newIdx, int oldIdx);
	void centerOrigin(sf::Text& text);
	int getHighlightedIdx();
protected:
	int windowSizeX;
	int windowSizeY;

	sf::Font font;
	sf::Text titleText;
	std::vector<sf::Text> items;

	int highlightedIdx;

};