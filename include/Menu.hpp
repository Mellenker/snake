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
	int m_windowSizeX;
	int m_windowSizeY;

	sf::Font m_font;
	sf::Text m_titleText;
	std::vector<sf::Text> m_items;

	int m_highlightedIdx;

};