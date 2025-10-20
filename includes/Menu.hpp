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

/*
Summary:
Because sf::Text requires a font at construction, and your font is loaded in the constructor body, you 
should use a pointer or std::optional for sf::Text so you can con
struct it after the font is loaded. This is a safe and modern C++17 approach.

N�R SKA MAN ANV�NDA POINTERS/REFERENCES? �R DETA ETT BRA L�GE ATT ANV�NDA POINTERS?

*/