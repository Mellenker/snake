#pragma once  
#include <SFML/Graphics.hpp>

// Parent class of menus
class Menu {
public:
	Menu();
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
private:
	void updateHighlighted(int newIdx, int oldIdx);
	void centerOrigin(sf::Text& text);
	int getHighlightedIdx();
};