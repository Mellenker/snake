#pragma once  
#include <SFML/Graphics.hpp>

// Parent class of menus
class Menu {
public:
	Menu(int titleCharSize, int itemCharSize);
	void moveUp();
	void moveDown();
	void draw(sf::RenderWindow& window);
protected:
	void setTitle(const std::string& string);
	void addItem(const std::string& string);

	sf::Font m_font;
	sf::Text m_titleText;
	std::vector<sf::Text> m_items;
	int m_highlightedIdx;

	int m_windowSizeX;
	int m_windowSizeY;

	int m_titleCharSize = 42;
	int m_itemCharSize = 30;

private:
	void updateHighlighted(int newIdx, int oldIdx);
	void centerOrigin(sf::Text& text);
	int getHighlightedIdx();
};