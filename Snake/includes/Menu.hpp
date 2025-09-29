#pragma once  

#include <SFML/Graphics.hpp>
#include "../includes/Utils.hpp"

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
	sf::Text titleText;

	int highlightedIdx;
	static constexpr int highlightedIdxInit = 0;

	std::vector<sf::Text> items;
	sf::Font font;
};